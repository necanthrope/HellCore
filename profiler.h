/******************************************************************************
  2009 The Hell Syndicate.

  Rights considered an annoyance of oppressive litigious society and 
  neither reserved nor recognized. Besides, how did you get this code?

  -- seraph
 *****************************************************************************/

#include "my-stdio.h"

extern void  set_profiler_file(FILE *);
extern FILE* get_profiler_file(void);

extern void profile_log(const char *,...);

/* 
 * $Log: profiler.h,v $
 * Revision 1.1  2009/07/25 03:21:59  blacklite
 * add profiling when PROFILE_VERBS is defined, spits info out to a profile log
 * (specify with -p). I may still be missing some spots but this seems to give
 * usable info right now.
 *
 */
