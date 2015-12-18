#ifndef Hash_h
#define Hash_h 1

#include <stdint.h>     /* defines uint32_t etc */

#define hashsize(n) ((uint32_t)1<<(n))
#define hashmask(n) (hashsize(n)-1)
#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))

extern uint32_t hashlittle( const void *key, size_t length, uint32_t initval);

#endif				/* Hash_h */
