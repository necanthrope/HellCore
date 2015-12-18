/******************************************************************************
  2009 The Hell Syndicate.

  Rights considered an annoyance of oppressive litigious society and 
  neither reserved nor recognized. Besides, how did you get this code?
 *****************************************************************************/


/*
 * It's mysql from inside moo!
 */

#include "options.h"

#ifdef MOOMYSQL
 
#include <mysql/mysql.h>
#include <stdlib.h>

#include "my-string.h"
 
#include "numbers.h"
#include "log.h"
#include "list.h"
#include "moomysql.h"
#include "storage.h"
#include "utils.h"

typedef struct mysql_session mysql_session;

struct mysql_session {
	moomysql_handle id;
	MYSQL *mysql;
	MYSQL_RES *current_result;
	MYSQL_FIELD *current_fields;
	unsigned int n_fields;
	mysql_session *next;
};

static mysql_session *session_first, *session_last;
static moomysql_handle next_id = 1;
static char* connection_error;

moomysql_handle
moomysql_open_connection(const char *host, const char *user, 
	const char *passwd, const char *db, unsigned int port, const char *unix_socket)
{
	MYSQL *mysql = mysql_init(NULL);
	
	if (!mysql) {
		errlog("Ran out of memory initializing mysql\n");
		return 0;
	}
	
	if (!mysql_real_connect(mysql, host, user, passwd, db, port, unix_socket, 0)) {
		errlog("Couldn't connect to mysql server %s:%d - %s\n", host, port,
			mysql_error(mysql));
		connection_error = (char*)mysql_error(mysql);
		return 0;
	}
	
	/* it worked, whoa */
	mysql_session *new_session = malloc(sizeof(mysql_session));
	
	new_session->id	= next_id++;
	new_session->mysql = mysql;
	new_session->next  = 0;
	new_session->current_result = 0;

	if (session_last == 0) {
		session_first = new_session;
		session_last  = new_session;
	} else {
		session_last->next = new_session;
		session_last	   = new_session;
	}
	
	oklog("MYSQL: Connected to %s:%d as user %s -- connection handle #%d\n", host, port, user,
		new_session->id);
	
	return new_session->id;
}

static mysql_session*
get_session(moomysql_handle h)
{
	if (session_first == 0)
		return 0;
	
	mysql_session *ptr;
	for (ptr = session_first; ptr != 0; ptr = ptr->next) {
		if (ptr->id == h)
			return ptr;
	}
	return 0;
}

void
moomysql_close_all_connections()
{
	mysql_session *ptr = session_first;
	int closed = 0;
	
	while (session_first != 0) {
		mysql_close(session_first->mysql);
		closed++;
		ptr = session_first->next;
		free(session_first);
		session_first = ptr;
	}
	
	session_last  = 0;
	if (closed)
		oklog("MYSQL: Closed all connections. (%d)\n", closed);
}

void
moomysql_close_connection(moomysql_handle h)
{
	if (session_first == 0)
		return;
	
	mysql_session *ptr, *prevptr;
	
	for (ptr = session_first, prevptr = 0; 
		 ptr != 0;
		 prevptr = ptr, ptr = ptr->next) {
		if (ptr->id == h) {
			mysql_close(ptr->mysql);
			oklog("MYSQL: Closed connection #%d\n", h);
			
			if (ptr->next == 0) {
				session_last = prevptr;
			}
			if (prevptr == 0) {
				session_first = ptr->next;
			} else {
				prevptr->next = ptr->next;
			}
			free(ptr);
			return;
		}
	}
	return;
}


static Var
mysql_error_as_var(MYSQL *m)
{
	Var r;
	r.type  = TYPE_STR;
	r.v.str = str_dup(mysql_error(m));
	return r;
}

Var
moomysql_error (moomysql_handle h)
{
	mysql_session *s = get_session(h);

	if (!s)
		return zero;

	return mysql_error_as_var(s->mysql);
}

#define MYSQL_MOO_NUMERIC (MYSQL_TYPE_TINY|MYSQL_TYPE_SHORT|MYSQL_TYPE_LONG|MYSQL_TYPE_INT24)
#define MYSQL_MOO_FLOAT (MYSQL_TYPE_DECIMAL|MYSQL_TYPE_FLOAT|MYSQL_TYPE_DOUBLE)
#define MYSQL_MOO_UNREPRESENTABLE (MYSQL_TYPE_LONGLONG|MYSQL_TYPE_GEOMETRY)

/* everything else is a string. */

static Var
list_from_row(MYSQL_ROW row, int n_fields, MYSQL_FIELD * fields, unsigned long *lengths)
{
	Var rowlist = new_list(n_fields);
	int i;
		
	for (i = 0; i < n_fields; i++) {
		Var data;
		unsigned long len = lengths[i];
		MYSQL_FIELD field = fields[i];

		if (len == 0) {
		   data.type = TYPE_ERR;
		   data.v.err = E_NONE;

		} else if (field.type & MYSQL_MOO_NUMERIC) {
		   data.type = TYPE_INT;
		   data.v.num = atoi((char*) row[i]);

		} else if (field.type & MYSQL_MOO_FLOAT) {
		   data = new_float(atof((char*) row[i]));

		} else if (field.type & MYSQL_MOO_UNREPRESENTABLE) {
		   data.type = TYPE_ERR;
		   data.v.err = E_TYPE;

		} else {
			data.type  = TYPE_STR;
			data.v.str = mymalloc(len+1, M_STRING);
			strncpy(data.v.str, row[i], len);

		} 
		rowlist.v.list[i + 1] = data;
	}
	return rowlist;
}

Var 
moomysql_next_row(moomysql_handle h)
{
   Var r;

   mysql_session *s = get_session(h);

   if (!s) {
		r.type = TYPE_ERR;
		r.v.err = E_INVARG;
		return r;
   }

   if (!(s->current_result)) {
		r.type = TYPE_ERR;
		r.v.err = E_RANGE;
   }
  
   MYSQL_ROW row = mysql_fetch_row(s->current_result);
   unsigned long *lengths = mysql_fetch_lengths(s->current_result);

   if (row) {
		r = list_from_row(row, s->n_fields, s->current_fields, lengths);
		return r;
   } else {
		mysql_free_result(s->current_result);
		s->current_result = NULL;
		s->current_fields = 0;

		return zero;
   }
}

/*   *
	 * Returns 1 on successful select, number of affected rows,
	 * if a sucessful non-select query;
	 * or a string, if something went wrong.
*/
Var
moomysql_send_query(moomysql_handle h, const char *query)
{
	Var r;
	mysql_session *s;
	
	if (query == 0) {
		r.type  = TYPE_STR;
		r.v.str = str_dup("Null query.");
		return r;
	}
	
	s = get_session(h);
	if (!s) {
		r.type  = TYPE_STR;
		r.v.str = str_dup("Invalid mysql handle.");
		return r;
	}
	
	if (mysql_query(s->mysql, query)) {
		return mysql_error_as_var(s->mysql);
	}
	
	MYSQL_RES *result = mysql_use_result(s->mysql);
	
	if (mysql_errno(s->mysql) != 0) {
		return mysql_error_as_var(s->mysql);
	}
	
	if (result) {
		s->current_result = result;
		s->current_fields = mysql_fetch_fields(result);
		s->n_fields = (int) mysql_num_fields(result);

		r.type = TYPE_INT;
		r.v.num = 1;
		return r;

	} else {
		/* this wasn't a select */
		
		r.type  = TYPE_INT;
		r.v.num = (int) mysql_affected_rows(s->mysql);
		return r;
	}
}

#endif /* MYSQL */

char rcsid_mysql[] = "$Id: moomysql.c,v 1.1 2010/05/16 02:39:23 blacklite Exp $";

/*   *
	 * $Log: moomysql.c,v $
	 * Revision 1.1  2010/05/16 02:39:23  blacklite
	 * Break out some IPC stuff into pipe_utils.c, add var serialization, and some unfinished mysql stuff
	 *
	 *
*/
