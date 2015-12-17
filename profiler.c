/******************************************************************************
  2009 The Hell Syndicate.

  Rights considered an annoyance of oppressive litigious society and 
  neither reserved nor recognized. Besides, how did you get this code?

  -- seraph
 *****************************************************************************/

#include <errno.h>
#include "my-stdarg.h"
#include "my-stdio.h"
#include "my-string.h"
#include "my-time.h"

#include "bf_register.h"
#include "config.h"
#include "functions.h"
#include "log.h"
#include "options.h"
#include "storage.h"
#include "streams.h"
#include "utils.h"

static FILE *pro_file = 0;

void
set_profiler_file(FILE * f)
{
    pro_file = f;
}

FILE*
get_profiler_file()
{
	return pro_file;
}

static void
do_profile_log(const char *fmt, va_list args)
{
    FILE *f;
    static struct timespec ts;
    static long last_sec  = 0;
    static long last_nsec = 0;

    clock_gettime ( CLOCK_THREAD_CPUTIME_ID, &ts );

    if (pro_file) {
	f = pro_file;
    } else
	f = stderr;

    if (last_sec != 0) {
	long diff_sec = ts.tv_sec - last_sec;
	long diff_nsec;
	if (diff_sec > 0) {
		diff_nsec = 1000000000 - last_nsec + ts.tv_nsec;
	} else {
		diff_nsec = ts.tv_nsec - last_nsec;
	}
	fprintf(f, "+%2li.%09li: ", diff_sec, diff_nsec);
    } else {
	fprintf(f, "+%2li.%09li: ", ts.tv_sec, ts.tv_nsec);
    }

    last_sec  = ts.tv_sec;
    last_nsec = ts.tv_nsec;

    vfprintf(f, fmt, args);
    fflush(f);
}

void
profile_log(const char *fmt,...)
{
    va_list args;

    va_start(args, fmt);
    do_profile_log(fmt, args);
    va_end(args);
}

char rcsid_profiler[] = "$Id: profiler.c,v 1.3 2009/10/11 00:27:57 blacklite Exp $";

/* 
 * $Log: profiler.c,v $
 * Revision 1.3  2009/10/11 00:27:57  blacklite
 * remove old ref to global.h
 *
 * Revision 1.2  2009/07/26 20:00:24  blacklite
 * measure time in difference from last line
 *
 * Revision 1.1  2009/07/25 03:21:59  blacklite
 * add profiling when PROFILE_VERBS is defined, spits info out to a profile log
 * (specify with -p). I may still be missing some spots but this seems to give
 * usable info right now.
 *
 */
