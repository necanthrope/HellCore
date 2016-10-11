/******************************************************************************
  Copyright (c) 1992, 1995, 1996 Xerox Corporation.	 All rights reserved.
  Portions of this code were written by Stephen White, aka ghond.
  Use and copying of this software and preparation of derivative works based
  upon this software are permitted.	 Any distribution of this software or
  derivative works must comply with all applicable United States export
  control laws.	 This software is made available AS IS, and Xerox Corporation
  makes no warranty about the software, its performance or its conformity to
  any specification.  Any person obtaining a copy of this software is requested
  to send their name and post office or electronic mail address to:
	Pavel Curtis
	Xerox PARC
	3333 Coyote Hill Rd.
	Palo Alto, CA 94304
	Pavel@Xerox.Com
 *****************************************************************************/

#include "my-stdlib.h"

#include "config.h"
#include "exceptions.h"
#include "list.h"
#include "options.h"
#include "log.h"
#include "ref_count.h"
#include "storage.h"
#include "structures.h"
#include "utils.h"

#ifdef MEMORY_TRACE

#define BACKTRACE_MAX 16

typedef struct Memrecord Memrecord;

struct Memrecord {
		void* mem;
		Memrecord* next;
		Memory_Type type;
		size_t size;
		char** alloc_bt;
		int bt_size;
		int touches;
		int id;
		int freed;
};

void* bt_buffer[BACKTRACE_MAX];
static Memrecord *first_mr, *last_mr;

static char* Memory_Type_Names[Sizeof_Memory_Type] =
{
	"AST_POOL", "AST", "PROGRAM", "PVAL", "NETWORK", "STRING", "VERBDEF",
	"LIST", "PREP", "PROPDEF", "OBJECT_TABLE", "OBJECT", "FLOAT",
	"STREAM", "NAMES", "ENV", "TASK", "PATTERN",

	"BYTECODES", "FORK_VECTORS", "LIT_LIST",
	"PROTOTYPE", "CODE_GEN", "DISASSEMBLE", "DECOMPILE",

	"RT_STACK", "RT_ENV", "BI_FUNC_DATA", "VM",

	"REF_ENTRY", "REF_TABLE", "VC_ENTRY", "VC_TABLE", "STRING_PTRS",
	"INTERN_POINTER", "INTERN_ENTRY", "INTERN_HUNK",
	
	"HASH"
};


static inline void print_memdump(Memrecord *m, const char *prefix, int detail, int print_value);
static int next_mem_id = 1;
static int live_trace = 0;
static Memrecord *now_reallocing;
#endif

static unsigned alloc_num[Sizeof_Memory_Type];

static inline int
refcount_overhead(Memory_Type type)
{
	/* These are the only allocation types that are addref()'d.
	 * As long as we're living on the wild side, avoid getting the
	 * refcount slot for allocations that won't need it.
	 *
	 * Lists get two because we allocate more than requested, 
	 * to make list expansion faster.
	 */
	switch (type) {
	case M_FLOAT:
		/* for systems with picky double alignment */
		return MAX(sizeof(int), sizeof(double));
	case M_STRING:
		return sizeof(int);
	case M_LIST:
	case M_HASH:
		/* for systems with picky pointer alignment */
		return MAX(sizeof(int), sizeof(Var *));
	case M_WAIF:
		/*for systems with picky pointer alignment */
		return MAX(sizeof(int), sizeof(void *));
	default:
		return 0;
	}
}

#ifdef MEMORY_TRACE
static inline void
track_mem(void* p, Memory_Type t, size_t sz)
{
	if (!live_trace)
		return;

#ifdef MEMORY_TRACE_TYPE
	if (t != MEMORY_TRACE_TYPE)
		return;
#endif
			
	if (last_mr == 0) {
		first_mr = malloc(sizeof(Memrecord));
		last_mr = first_mr;
	} else {
		last_mr->next = malloc(sizeof(Memrecord));
		last_mr = last_mr->next;
	}

	last_mr->mem  = p;
	last_mr->next = 0;
	last_mr->type = t;
	last_mr->size = sz;
	last_mr->bt_size  = backtrace(bt_buffer, BACKTRACE_MAX);
	last_mr->alloc_bt = backtrace_symbols(bt_buffer, last_mr->bt_size);
	last_mr->touches  = 1;
	last_mr->id = next_mem_id++;
	last_mr->freed = 0;

	if (live_trace >= 2)
		print_memdump(last_mr, "ALLOC   ", live_trace == 3, 0);
}

static inline void
find_mem(void *p)
{
	Memrecord *m;
	
	for (m = first_mr; m; m = m->next) {
		if (m->mem == p) {
			now_reallocing = m;
			if (m->freed) {
				print_memdump(m, "PREVIOUSLY FREED -- TRYING TO REALLOC", 1, 0);
				abort();
			}
			return;
		}
	}
}

static inline void
update_mem(void *newp, int newsz)
{
	Memrecord *m = now_reallocing;
	if (!m)
		return;

	m->mem  = newp;
	m->size = newsz;
	m->bt_size  = backtrace(bt_buffer, BACKTRACE_MAX);
	m->alloc_bt = backtrace_symbols(bt_buffer, last_mr->bt_size);
	m->touches += 1;
	if (live_trace >= 2)
		print_memdump(m, "REALLOC ", live_trace == 3, 0);
	
	now_reallocing = 0;
}

static inline void
print_memdump(Memrecord *m, const char *prefix, int detail, int print_value)
{
	int i;
	
	oklog("--- %s: %5d bytes (%s %4d) at %p -- refs %2d\n",
	  prefix, m->size, Memory_Type_Names[m->type], m->id,
	  m->mem,
	  ((int *) (m->mem))[-1]
	);

	if (m->freed || detail == 1) {
		oklog("--- %s:    touch %d in:\n", prefix, m->touches);
      	  	if (m->type == M_STRING) {
			oklog("--- %s:    \"%s\"\n", prefix, m->mem);
        	}
		for (i = 1; i < m->bt_size && i < 7; i++) {
			oklog("--- %s:    %s\n", prefix, (m->alloc_bt)[i]);
		}
		if (m->freed) {
			oklog("--- %s: *** MEMORY WAS PREVIOUSLY FREED ***\n", prefix);
	                abort();
		}
	}
	if (print_value == 1 && (m->type == M_LIST || m->type == M_HASH)) {
		Var v;

		v.type = TYPE_LIST;
		v.v.list = m->mem;

		oklog("--- %s:    value: %s\n", prefix, value_to_literal(v));
	}
	if (print_value == 1 && m->type == M_STRING) {
		oklog("--- %s:    value: \"%s\"\n", prefix, m->mem);
	}
}

extern int
record_ref(void *ptr, int change)
{
	Memrecord *m;
	
	for (m = first_mr; m; m = m->next) {
		if (m->mem == ptr) {
			free(m->alloc_bt);
			
			m->bt_size  = backtrace(bt_buffer, BACKTRACE_MAX);
			m->alloc_bt = backtrace_symbols(bt_buffer, m->bt_size);
			m->touches += 1;
			if (live_trace >= 2) {
			    if (change == 0) {
				print_memdump(m, "CHECK   ", live_trace == 3, live_trace == 3);
			    } else if (change > 0){
				print_memdump(m, "ADD REF ", live_trace == 3, live_trace == 2);
			    } else {
				print_memdump(m, "DEL REF ", live_trace == 3, live_trace == 2);
			    }
			}

			return 0;
		}
	}

	/* found nothing */		
	/* could abort() */
	return 0;
}

static inline void
trackfree_mem(void *p)
{
        Memrecord *m;

        for (m = first_mr; m; m = m->next) {
                if (m->mem == p) {
			if (live_trace >= 2)
				print_memdump(m, "FAKEFREE", live_trace == 3, live_trace == 3);
			m->freed = 1;
			return;
		}
	}
}

static inline void
untrack_mem(void *p)
{
	Memrecord *prev, *m;

	for(prev = 0, m = first_mr;
		m;
		prev = m, m = m->next) {
		if (m->mem == p) {
			if (prev)
				prev->next = m->next;
			if (m == first_mr)
				first_mr   = m->next;
			if (m == last_mr)
				last_mr	   = prev;
		
			if (live_trace >= 2)	
				print_memdump(m, "FREE    ", live_trace == 3, 0);
			free(m->alloc_bt);
			free(m);
			return;
		}
	}

	/* found nothing */		
	/* could abort() */
}

void
verify_mem()
{
	Memrecord *m;
	int offs, i;
	
	oklog("--- MEMCHECK ---\n");
	for (m = first_mr; m; m = m->next) {
		if (!m->freed)
			print_memdump(m, "MEMCHECK", 1, 1);
	}
	oklog("--- COMPLETE ---\n");
}
#else /* !MEMORY_TRACE */

#define track_mem(a,b,c)
#define find_mem(x)
#define update_mem(a,b)
#define trackfree_mem(x)
#define untrack_mem(x)

#endif 


void *
mymalloc(unsigned size, Memory_Type type)
{
	char *memptr;
	char msg[100];
	int offs;

	if (size == 0)				/* For queasy systems */
		size = 1;

	offs = refcount_overhead(type);
	memptr = (char *) malloc(size + offs);
	if (!memptr) {
		sprintf(msg, "memory allocation (size %u) failed!", size);
		panic(msg);
	}
	alloc_num[type]++;

	if (offs) {
		memptr += offs;
		((int *) memptr)[-1] = 1;
	}

	track_mem(memptr, type, size);
	return memptr;
}

const char *
str_ref(const char *s)
{
	addref(s);
	return s;
}

char *
str_dup(const char *s)
{
	char *r;

	if (s == 0 || *s == '\0') {
		static char *emptystring;

		if (!emptystring) {
			emptystring = (char *) mymalloc(1, M_STRING);
			*emptystring = '\0';
		}
		addref(emptystring);
		return emptystring;
	} else {
		r = (char *) mymalloc(strlen(s) + 1, M_STRING);
		strcpy(r, s);
	}
	return r;
}

void *
myrealloc(void *ptr, unsigned size, Memory_Type type)
{
	int offs = refcount_overhead(type);
	static char msg[100];

	find_mem(ptr);
	ptr = realloc((char *) ptr - offs, size + offs);
	if (!ptr) {
		sprintf(msg, "memory re-allocation (size %u) failed!", size);
		panic(msg);
	}

	ptr = (void*)((char*)ptr + offs);
	
	update_mem(ptr, size);

	return ptr;
}

void
myfree(void *ptr, Memory_Type type)
{
	if (!ptr) {
		panic("Got null pointer in myfree");
	}
		
	alloc_num[type]--;

#ifdef FAKE_FREE
	trackfree_mem(ptr);
	memset(ptr, 0, 1);
#else
	untrack_mem(ptr);
	ptr = (void*)( (char*)ptr - refcount_overhead(type) );
	free(ptr);
#endif
}

Var
memory_usage(void)
{
	Var r;
	int total_alloc, i;

	/* We want to return {totalitems, each item, ...} */
	r = new_list(Sizeof_Memory_Type + 1);
	total_alloc = 0;
	
	/* do the individual items first, starting from index 3. */
	for (i = 0; i < Sizeof_Memory_Type; i++) {
		r.v.list[i+2].type = TYPE_INT;
		r.v.list[i+2].v.num = alloc_num[i];
		total_alloc += alloc_num[i];
	}
	
	r.v.list[1].type = TYPE_INT;
	r.v.list[1].v.num = total_alloc;

	return r;
}

#ifdef MEMORY_TRACE
int set_live_trace(int live_trace_on)
{
	live_trace = live_trace_on;
}
#endif

char rcsid_storage[] = "$Id: storage.c,v 1.9 2009/09/29 20:44:32 blacklite Exp $";

/* 
 * $Log: storage.c,v $
 * Revision 1.9  2009/09/29 20:44:32  blacklite
 * Add new trackfree_mem null macro, and change an abort to panic.
 *
 * Revision 1.8  2009/08/14 21:34:10  blacklite
 * add new levels to live_trace (1, don't spam stderr; 2 spam stderr; 3 spam with backtraces and values)
 *
 * Revision 1.7  2009/08/14 16:48:13  blacklite
 * add special handling for memory tracing when FAKE_FREE is on, basically emulate the sort of thing that valgrind et al do, don't free anything, and then abort if old, supposedly-freed memory gets used. also move checks to the front in ref_count.h macros so they happen -before- the actual pointer dereference, so we abort before a double free.
 *
 * Revision 1.6  2009/03/08 12:41:31  blacklite
 * Added HASH data type, yield keyword, MEMORY_TRACE, vfscanf(),
 * extra myrealloc() and memcpy() tricks for lists, Valgrind
 * support for str_intern.c, etc. See ChangeLog.txt.
 *
 * Revision 1.5	 2008/08/24 05:09:16  blacklite
 * add PADDED_LIST_ALLOC, but disable it by default, because it doesn't quite work yet. also remove the 'itemsize' from memory_usage since it is actually useless.
 *
 * Revision 1.4	 2008/08/22 22:10:04  blacklite
 * Make memory_usage() useful even when !USE_GNU_MALLOC.
 *
 * Revision 1.3	 2007/09/12 07:33:29  spunky
 * This is a working version of the current HellMOO server
 *
 * Revision 1.5	 1998/12/14 13:18:59  nop
 * Merge UNSAFE_OPTS (ref fixups); fix Log tag placement to fit CVS whims
 *
 * Revision 1.4	 1997/07/07 03:24:55  nop
 * Merge UNSAFE_OPTS (r5) after extensive testing.
 *
 * Revision 1.3.2.3	 1997/05/29 20:47:32  nop
 * Stupid hack to allow non-gcc compilers to use -Dinline= to make the server
 * compile.
 *
 * Revision 1.3.2.2	 1997/03/21 15:19:23  bjj
 * add myrealloc interface, inline free_str
 *
 * Revision 1.3.2.1	 1997/03/20 18:59:26  bjj
 * Allocate refcounts with objects that can be addref()'d (strings, lists,
 * floats).	 Use macros to manipulate those counts.	 This completely replaces
 * the external hash table addref and friends.
 *
 * Revision 1.3	 1997/03/03 06:32:10  bjj
 * str_dup("") now returns the same empty string to every caller
 *
 * Revision 1.2	 1997/03/03 04:19:26  nop
 * GNU Indent normalization
 *
 * Revision 1.1.1.1	 1997/03/03 03:45:01  nop
 * LambdaMOO 1.8.0p5
 *
 * Revision 2.1	 1996/02/08	 06:51:20  pavel
 * Renamed TYPE_NUM to TYPE_INT.  Updated copyright notice for 1996.
 * Release 1.8.0beta1.
 *
 * Revision 2.0	 1995/11/30	 04:31:30  pavel
 * New baseline version, corresponding to release 1.8.0alpha1.
 *
 * Revision 1.16  1992/10/23  23:03:47	pavel
 * Added copyright notice.
 *
 * Revision 1.15  1992/10/21  03:02:35	pavel
 * Converted to use new automatic configuration system.
 *
 * Revision 1.14  1992/10/17  20:52:37	pavel
 * Global rename of strdup->str_dup, strref->str_ref, vardup->var_dup, and
 * varref->var_ref.
 *
 * Revision 1.13  1992/09/14  18:38:42	pjames
 * Updated #includes.  Moved rcsid to bottom.
 *
 * Revision 1.12  1992/09/14  17:41:16	pjames
 * Moved db_modification code to db modules.
 *
 * Revision 1.11  1992/09/03  16:26:29	pjames
 * Added TYPE_CLEAR handling.
 * Changed property definition manipulating to work with arrays.
 *
 * Revision 1.10  1992/08/31  22:25:27	pjames
 * Changed some `char *'s to `const char *'
 *
 * Revision 1.9	 1992/08/28	 16:21:13  pjames
 * Changed vardup to varref.
 * Changed myfree(*, M_STRING) to free_str(*).
 * Added `strref()' and `free_str()'
 *
 * Revision 1.8	 1992/08/21	 00:42:18  pavel
 * Renamed include file "parse_command.h" to "parse_cmd.h".
 *
 * Changed to conditionalize on the option USE_GNU_MALLOC instead of
 * USE_SYSTEM_MALLOC.
 *
 * Removed use of worthless constant DB_INITIAL_SIZE, defined in config.h.
 *
 * Revision 1.7	 1992/08/14	 00:00:45  pavel
 * Converted to a typedef of `var_type' = `enum var_type'.
 *
 * Revision 1.6	 1992/08/10	 16:52:45  pjames
 * Updated #includes.
 *
 * Revision 1.5	 1992/07/30	 21:23:10  pjames
 * Casted malloc to (void *) because of a problem with some system.
 *
 * Revision 1.4	 1992/07/27	 19:05:18  pjames
 * Removed a debugging statement.
 *
 * Revision 1.3	 1992/07/27	 18:17:41  pjames
 * Changed name of ct_env to var_names and M_CT_ENV to M_NAMES.
 *
 * Revision 1.2	 1992/07/21	 00:06:38  pavel
 * Added rcsid_<filename-root> declaration to hold the RCS ident. string.
 *
 * Revision 1.1	 1992/07/20	 23:23:12  pavel
 * Initial RCS-controlled version.
 */
