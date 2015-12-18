/******************************************************************************
  Copyright (c) 1994, 1995, 1996 Xerox Corporation.  All rights reserved.
  Portions of this code were written by Stephen White, aka ghond.
  Use and copying of this software and preparation of derivative works based
  upon this software are permitted.  Any distribution of this software or
  derivative works must comply with all applicable United States export
  control laws.  This software is made available AS IS, and Xerox Corporation
  makes no warranty about the software, its performance or its conformity to
  any specification.  Any person obtaining a copy of this software is requested
  to send their name and post office or electronic mail address to:
	Pavel Curtis
	Xerox PARC
	3333 Coyote Hill Rd.
	Palo Alto, CA 94304
	Pavel@Xerox.Com
 *****************************************************************************/

/* This module provides IP host name lookup with timeouts.  Because
 * longjmps out of name lookups corrupt some UNIX name lookup modules, this
 * module uses a subprocess to do the name lookup.  On any failure, the
 * subprocess is restarted.
 */

#include "options.h"

#ifdef MOOMYSQL

#include "my-signal.h"
#include "my-stdlib.h"
#include "my-unistd.h"

#include "my-wait.h"
#include "my-string.h"

#include "execute.h"
#include "functions.h"

#include "config.h"
#include "list.h"
#include "log.h"
#include "server.h"
#include "storage.h"
#include "timers.h"
#include "net_multi.h"
#include "tasks.h"
#include "exceptions.h"
#include "serialize.h"

#include "pipe_utils.h"				/* spawn_pipe, ensure_buffer, robust_read */
#include "moomysql.h"
#include "utils.h"


#define SQLHOST "localhost"
#define SQLUSER "moo"
#define SQLPASS "moopass"
#define SQLDB "moodb"
#define SQLPORT 3306

/******************************************************************************
 * Data structures and types used by more than one process.
 *****************************************************************************/

struct sql_request {
	enum {
		SQLREQ_NEW_HANDLE, SQLREQ_DO_QUERY, SQLREQ_GET_ROW,
		SQLREQ_CLOSE_HANDLE, SQLREQ_ERROR
	} kind;
	unsigned length;
	unsigned timeout;
};

/******************************************************************************
 * Code that runs in the mysql-client process.
 *****************************************************************************/

static moomysql_handle my_handle = 0;

static void
end_sql(void)
{
	moomysql_close_connection(my_handle);
	_exit(1);
}

static void
timeout_proc(Timer_ID id, Timer_Data data)
{
	end_sql();
}

static void
do_mysql_comms(int to_server, int from_server)
{
	struct sql_request req;
	static char *buffer = 0;
	static int buflen = 0;
	static char *serial;
	Timer_ID id;
	Var args;
	Var result;

	set_server_cmdline("(MOO mysql-client slave)");

	my_handle = moomysql_open_connection(SQLHOST, SQLUSER, SQLPASS, SQLDB, SQLPORT, 0);

	for (;;) {
		oklog("MYSQL CHILD: ready to read!\n");
		if (robust_read(from_server, &req, sizeof(req)) != sizeof(req))
			end_sql();

		oklog("MYSQL CHILD read!\n");

		if (req.length) {
			ensure_buffer(&buffer, &buflen, req.length + 1);
			if (robust_read(from_server, buffer, req.length)
			  != req.length)
				end_sql();
			buffer[req.length] = '\0';
			oklog("MYSQL CHILD got stuff!\n");
			args = deserialize(buffer);
		}


		id = set_timer(req.timeout, timeout_proc, 0);

		if (req.kind == SQLREQ_DO_QUERY) {
			oklog("MYSQL CHILD: doing query '%s'\n", args.v.list[1].v.str);
			result = moomysql_send_query(my_handle, args.v.list[1].v.str);
			oklog("got result: %s\n", value2str(result));
			serial = serialize(result);
			oklog("MYSQL CHILD: serialized!\n");
			req.length = strlen(serial);
			oklog("MYSQL CHILD: strlenned!\n");

		} else if (req.kind == SQLREQ_GET_ROW) {
			result = moomysql_next_row(my_handle);
			serial = serialize(result);
			req.length = strlen(serial);

		} else {
			req.kind = SQLREQ_ERROR;
			req.length = 0;

		}

		oklog("MYSQL CHILD: writing..\n");
		write(to_server, &req, sizeof(req));
		oklog("MYSQL CHILD: wrote req..\n");
		if (req.length) {
			write(to_server, serial, req.length);
			oklog("MYSQL CHILD: wrote serial..\n");
			free(serial);
			oklog("MYSQL CHILD: freed serial!\n");
		}

	}

}

/******************************************************************************
 * Code that runs in the server process.
 *****************************************************************************/

typedef struct mysql_task {
	struct mysql_task *next;
/*	struct mysql_pipe *pipe; */
	vm the_vm;
	struct sql_request req;	
	char *to_send;
} mysql_task;

#if 0
typedef struct mysql_pipe {
	int to_mysql_fd;
	int from_mysql_fd;
	int handle;
	int n_active;
	int is_open;
	struct mysql_task *tasks;
	struct mysql_pipe *next;
} mysql_pipe;

static mysql_pipe *all_pipes = 0;

static void
close_pipe(mysql_pipe *p)
{
	return;

	/* 
	if (!p->is_open)
		return;
	network_unregister_fd(p->from_mysql_fd);
	close(p->to_mysql_fd);
	close(p->from_mysql_fd);
	p->is_open = 0;
	*/
}

static void mysqlchild_readable(int fd, void *data);

static mysql_pipe*
prepare_pipe(void)
{
	mysql_pipe* p = mymalloc(sizeof(mysql_pipe), M_TASK);

/*
	mysql_task* t = mymalloc(sizeof(mysql_task), M_TASK);
	t->next = 0;
	t->pipe = p;
	t->req.len = 0;
	t->to_send = 0;
*/
	
	p->handle = -1;
	p->n_active = 1;
/*	p->tasks = t; */
	p->next = all_pipes;
	p->is_open = 0;

	all_pipes = p;

}

#endif

int to_mysql_fd;
int from_mysql_fd;
mysql_task *tasks = 0;

static void mysqlchild_readable(int fd, void *data);

void
open_mysql(void)
{
	spawn_pipe(do_mysql_comms, &to_mysql_fd, &from_mysql_fd);
	network_register_fd(from_mysql_fd, mysqlchild_readable, 0, &(tasks));
}

/*
static mysql_pipe*
find_pipe_for_handle(int h)
{
	mysql_pipe *p = all_pipes;
	
	while (p) {
		if (p->handle == h)
			return p;

		p = p->next;
	}
	return 0;
}

static void
add_task_to_pipe(mysql_pipe *p, mysql_task *t)
{
	t->next = p->tasks;
	p->tasks = t;
	t->pipe = p;
}
*/

static void
send_on_pipe(struct sql_request req, char* to_send)
{
	write(to_mysql_fd, &req, sizeof(req));
	if (req.length > 0) {
		write(to_mysql_fd, to_send, req.length);
	}
}

/*
static void
remove_task_from_pipe(mysql_pipe *p, mysql_task *t)
{
	mysql_task *ptr = p->tasks;

	if (ptr == t) {
		p->tasks = t->next;
		return;
	}

	while (ptr->next) {
		if (ptr->next = t) {
			ptr->next = t->next;
			return;
		}
		ptr = ptr->next;
	}
}
*/

static task_enum_action
mysql_enumerator(task_closure closure, void *data)
{
	mysql_task *t;
	mysql_task *prev_t;

		prev_t = 0;
		t = tasks;

		while (t) {
			task_enum_action tea = (*closure) (t->the_vm, "mysql-waiting", data);

			if (tea == TEA_KILL) {
				if (prev_t)
					prev_t->next = t->next;

				if (t->to_send)
					free(t->to_send);
				myfree(t, M_TASK);
			} else if (tea != TEA_CONTINUE) {
				return tea;
			}

			prev_t = t;
			t = t->next;
		}

	return TEA_CONTINUE;
}

static void
mysqlchild_readable(int fd, void *data)
{
	struct sql_request req;

	mysql_task **tptr = data;
	mysql_task *t = *tptr;
/*	mysql_pipe *p = t->pipe; */

	static char *buffer = 0;
	static int buflen = 0;
	static char *serial;
	Var r;

	if (from_mysql_fd != fd)
		panic("MYSQLCHILD_READABLE: fd doesn't match from_mysql_fd!");

	if (robust_read(fd, &req, sizeof(req)) != sizeof(req)) {
		errlog("MYSQLCHILD_READABLE: req read failed\n");
		req.kind = SQLREQ_ERROR;
	} else {

		if (req.length != 0) {
			ensure_buffer(&buffer, &buflen, req.length + 1);
			if (robust_read(fd, buffer, req.length) != sizeof(req.length)) {
				errlog("MYSQLCHILD_READABLE: str read failed\n");
				req.kind = SQLREQ_ERROR;
				req.length = 0;
			}
			buffer[req.length] = '\0';

		} else {
			req.kind = SQLREQ_ERROR;
		}
	}

	switch (req.kind) {
	case SQLREQ_ERROR:
		r.type = TYPE_ERR;
		r.v.err = E_INVARG;
		break;
	case SQLREQ_CLOSE_HANDLE:
	case SQLREQ_NEW_HANDLE:
	case SQLREQ_DO_QUERY:
	case SQLREQ_GET_ROW:
		r = deserialize(buffer);
	}

	enqueue_from_enumerator(t->the_vm, r);
	myfree(t, M_TASK);
}

static enum error
mysql_suspender(vm the_vm, void *data)
{
	mysql_task *t = data;

	t->the_vm = the_vm;
	send_on_pipe(t->req, t->to_send);

	return E_NONE;
}
/*
static package
bf_mysql_new_handle(Var arglist, Byte next, void *vdata, Objid progr)
{
	mysql_pipe *p = prepare_pipe();
	p->t->req.kind = SQLREQ_NEW_HANDLE;
	p->t->req.length = 0;
	p->t->to_send = 0;
	free_var(arglist);
   
	return make_suspend_pack(mysql_suspender, p->t); 
}
*/

static package  
bf_mysql_next_row(Var arglist, Byte next, void *vdata, Objid progr)
{    
	mysql_task* t = mymalloc(sizeof(mysql_task), M_TASK);

	t->next = tasks;
	tasks = t;
	
    t->req.kind = SQLREQ_GET_ROW;
	t->req.length = 0;
    t->to_send = 0;
    free_var(arglist);
        
    return make_suspend_pack(mysql_suspender, t);
}

static package  
bf_mysql_query(Var arglist, Byte next, void *vdata, Objid progr)
{           
    mysql_task* t = mymalloc(sizeof(mysql_task), M_TASK);

    t->next = tasks;
    tasks = t;

    t->req.kind = SQLREQ_DO_QUERY;
    t->to_send = serialize(arglist);
    t->req.length = strlen(t->to_send);
    free_var(arglist);
        
    return make_suspend_pack(mysql_suspender, t);
}

/*
static package
bf_mysql_close(Var arglist, Byte next, void *vdata, Objid progr)
{
    mysql_pipe *p = all_pipes;

    if (!p) {
        free_var(arglist);
        return make_error_pack(E_INVARG);
    }
    p->t->req.kind = SQLREQ_CLOSE_HANDLE;
    p->t->to_send = serialize(arglist);
	p->t->req.length = strlen(p->t->to_send);

    free_var(arglist);

    return make_suspend_pack(mysql_suspender, p->t);
}
*/

void
register_mysql()
{
    register_task_queue(mysql_enumerator);
    register_function("mysql_next_row", 0, 0, bf_mysql_next_row);
	register_function("mysql_query", 1, 1, bf_mysql_query, TYPE_STR);
}

#endif

char rcsid_mysql_child[] = "$Id: mysql_child.c,v 1.1 2010/05/16 02:39:23 blacklite Exp $";

/* 
 * $Log: mysql_child.c,v $
 * Revision 1.1  2010/05/16 02:39:23  blacklite
 * Break out some IPC stuff into pipe_utils.c, add var serialization, and some unfinished mysql stuff
 *
 *
 */
