/******************************************************************************
  2009 The Hell Syndicate.

  Rights considered an annoyance of oppressive litigious society and 
  neither reserved nor recognized. Besides, how did you get this code?

  -- seraph
 *****************************************************************************/

#include "structures.h"

#define INITIAL_HASH_SIZE 16
#define HASH_RESERVED 1
#define HASH_START    1 + HASH_RESERVED

extern Var new_hash(void);
extern Var hashset(Var hash, Var key, Var value);
extern Var hashget(Var hash, Var key);

extern Var hashiterate(Var hash, Var * hashentry, Var iterator);

extern int hashcontains(Var hash, Var key);
extern int hashlength(Var hash);

/* this is for db i/o and var_dup */
extern Var alloc_list_for_hash(int count);

/* 
 * $Log: hash.h,v $
 * Revision 1.2  2009/07/22 19:27:09  blacklite
 * Fixed bug where a dup'd hash pointed to old hashes' keys/values.
 *
 * Revision 1.1  2009/03/08 12:41:31  blacklite
 * Added HASH data type, yield keyword, MEMORY_TRACE, vfscanf(),
 * extra myrealloc() and memcpy() tricks for lists, Valgrind
 * support for str_intern.c, etc. See ChangeLog.txt.
 *
 */
