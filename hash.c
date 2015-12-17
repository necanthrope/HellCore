/******************************************************************************
  2009 The Hell Syndicate.

  Rights considered an annoyance of oppressive litigious society and 
  neither reserved nor recognized. Besides, how did you get this code?

  -- seraph
 *****************************************************************************/

#include "my-ctype.h"
#include "my-string.h"
#include "my-stdlib.h"
#include "my-stdarg.h"

#include "bf_register.h"
#include "config.h"
#include "exceptions.h"
#include "functions.h"
#include "hash.h"
#include "numbers.h"
#include "list.h"
#include "log.h"
#include "options.h"
#include "ref_count.h"
#include "streams.h"
#include "storage.h"
#include "structures.h"
#include "unparse.h"
#include "utils.h"
#include "hash_lookup.h"

static Var hashexpand(Var hash);
static Var hashexpand_in_advance(Var hash, int keys_to_add);

/*
The best hash table sizes are powers of 2.  There is no need to do
mod a prime (mod is sooo slow!).  If you need less than 32 bits,
use a bitmask.  For example, if you need only 10 bits, do
  h = (h & hashmask(10));
In which case, the hash table should have hashsize(10) elements.

hashlittle( const void *key, size_t length, uint32_t initval);
*/

#define HASH_ALLOCATION_SIZE (INITIAL_HASH_SIZE + HASH_RESERVED)

/* we're not trying to be hacker-proof or anything, so 
 * let's not bother with random() and seeding and all that
 */
#define HASH_INITVAL 1694232671


Var
alloc_list_for_hash(int size)
{
    Var new;

    new.type   = TYPE_HASH;
    new.v.list = (Var *) mymalloc((size + 1) * sizeof(Var), M_HASH);
    new.v.list[0].type = TYPE_INT;
    new.v.list[0].v.num = size;
    return new;	
}

Var
new_hash(void)
{
	Var new;
	int i;
	
	new = alloc_list_for_hash(HASH_ALLOCATION_SIZE);
	
	/* we reserve 1 Var for the number of set elements 
	 * in the hash, so we start zeroing from 1, which
	 * includes our reserved space. */
	for (i = 1; i <= HASH_ALLOCATION_SIZE; i++) {
		new.v.list[i] = zero;
	}
	
    	return new;
}

static inline
void
inc_keycount(Var hash)
{
	(hash.v.list[1].v.num)++;
}

static inline
void
dec_keycount(Var hash)
{
	(hash.v.list[1].v.num)--;
}

static inline
int
keycount(Var hash)
{
	return (hash.v.list[1].v.num);
}

static inline
int
hash_end(Var hash)
{
	return (hash.v.list[0].v.num);
}

static inline
int
hash_slots(Var hash)
{
	return (hash.v.list[0].v.num - HASH_RESERVED);
}

/* external use keycount func */
int
hashlength(Var hash)
{
	return keycount(hash);
}

static int
index_for(Var hash, Var key)
{
	unsigned int index;
	
	if (key.type == TYPE_STR) {
		index = hashlittle(key.v.str, strlen(key.v.str), HASH_INITVAL);
	} else if (key.type == TYPE_FLOAT) {
		index = hashlittle(key.v.fnum, sizeof(double), HASH_INITVAL);
	} else if (key.type == TYPE_INT || key.type == TYPE_OBJ 
		   || key.type == TYPE_ERR) {
		index = hashlittle(&(key.v.num), sizeof(int32), HASH_INITVAL);
	} else {
		panic("invalid var type in index_for()");
	}
	index = index & (hash_end(hash) - HASH_RESERVED - 1);
	index = index + HASH_START;
		
	return index;
}

Var
hashset(Var hash, Var key, Var value)
{
	Var chain;
	int index;

	if (hash.type != TYPE_HASH) {
		panic("got non-hash in hashset!");
	}
	if (hash.v.list[0].v.num == 0) {
		panic("got 0-length list in hashset!");
	}

	hash = hashexpand_in_advance(hash, 1);
	
	if (hash.type == TYPE_ERR) {
		return hash;
	}

	index = index_for(hash, key);
	chain = hash.v.list[index];
	
	if (hash.v.list[index].type != TYPE_LIST) {
		/* free spot -- easy as pie */
		chain = new_list(2);

		chain.v.list[1] = key;
		chain.v.list[2] = value;
		
		listset(hash,chain,index);
		inc_keycount(hash);
		return hash;
	}

	/* no free spot, let's see if it's here somewhere... */
	int subindex;
	
	for (subindex = 1; subindex <= chain.v.list[0].v.num; subindex += 2) {
		if (equality(chain.v.list[subindex], key, 1)) {			
			free_var(key); /* since we already have it */
			free_var(chain.v.list[subindex+1]);
			chain.v.list[subindex+1] = value;
			return hash;
		}
	}
	
	/* it's not in the chain, tack it on the end */
	int size = chain.v.list[0].v.num;

	if (var_refcount(chain) == 1) {
		/* realloc  -- size + 3 is old list, plus 0-space for size, plus 2 for new entry */
		chain.v.list = (Var *) myrealloc(chain.v.list, (size + 3) * sizeof(Var), M_LIST);
		chain.v.list[0].v.num = size + 2;
		chain.v.list[size + 1] = key;
		chain.v.list[size + 2] = value;
		
		hash.v.list[index] = chain;
	} else {
		Var new_chain;
		int i;
		
		new_chain = new_list(size + 2);
		for (i = 1; i <= size; i++)
			new_chain.v.list[i] = var_ref(chain.v.list[i]);
		
		new_chain.v.list[size + 1] = key;
		new_chain.v.list[size + 2] = value;
		
		free_var(chain);
		hash.v.list[index] = new_chain;
	}

	inc_keycount(hash);
	return hash;
}

Var
hashget(Var hash, Var key)
{
	int index;
	int subindex;
	static Var novalue;
	
	if (novalue.type == 0) {
		novalue.type = TYPE_NONE;
	}
	
	index = index_for(hash, key);
	
	if (hash.v.list[index].type == TYPE_LIST) {
		for (subindex = 1; subindex <= hash.v.list[index].v.list[0].v.num; subindex += 2) {
			if (equality(hash.v.list[index].v.list[subindex], key, 1)) {
				return var_dup(hash.v.list[index].v.list[subindex + 1]);
			}
		}
	}
	return novalue;
}

int
hashcontains(Var hash, Var key)
{
	int index;
	
	index = index_for(hash, key);

	if (hash.v.list[index].type == TYPE_LIST) {
		int subindex;

		for (subindex = 1; subindex <= hash.v.list[index].v.list[0].v.num; subindex += 2) {
			if (equality(hash.v.list[index].v.list[subindex], key, 1)) {
				return 1;
			}
		}
	}
	return 0;
}

/* 
 * set hashentry to the key & value of the next item
 * and return something to be passed back in next
 * time. if we return INT > sizeofhash, stop.
 * 
 * when starting, iterator must be INT 1.
 */

Var
hashiterate(Var hash, Var * hashentry, Var iterator)
{
	int index, subindex, found = 0, madeloop = 0;
	Var realentry;
	
	if (iterator.type == TYPE_INT && iterator.v.num == 1) {
		/* start a new iteration, if we have any keys */
		if (keycount(hash) < 1) {
			iterator.type  = TYPE_ERR;
			iterator.v.err = E_NONE;
			return iterator;
		}
		
		/* iterator = {x,y} indicating index & subindex in hash */
		iterator = new_list(2);
		iterator.v.list[1].type  = TYPE_INT;
		iterator.v.list[1].v.num = HASH_START;
		iterator.v.list[2].type  = TYPE_INT;
		iterator.v.list[2].v.num = 1;
	}
	
	index    = iterator.v.list[1].v.num;
	subindex = iterator.v.list[2].v.num;

	for (; index <= hash_end(hash); index++) {
		Var chain = hash.v.list[index];
		if (chain.type != TYPE_LIST)
			continue;
		
		if (madeloop)
			subindex = 1;
		for (; subindex <= chain.v.list[0].v.num; subindex += 2) {
			if (found) {
				/* this is our second one, so return the spot for later */
				iterator.v.list[1].v.num = index;
				iterator.v.list[2].v.num = subindex;
				return iterator;
			}

			/* stuff this into hashentry */
			realentry = new_list(2);
			realentry.v.list[1] = var_dup(chain.v.list[subindex]);
			realentry.v.list[2] = var_dup(chain.v.list[subindex+1]);
			hashentry->type   = TYPE_LIST;
			hashentry->v.list = realentry.v.list;
			
			found = 1;
		}
		madeloop = 1;
	}

	/* we got nothin', return */
	free_var(iterator);
	iterator.type  = TYPE_INT;
	iterator.v.num = hash.v.list[0].v.num + 1;
	return iterator;
}


inline static Var
subchain(Var chain, int lower, int upper)
{
	Var r;
	int i;

	r = new_list(upper - lower + 1);
	for (i = lower; i <= upper; i++)
	    r.v.list[i - lower + 1] = var_ref(chain.v.list[i]);
	free_var(chain);
	return r;
}

inline static void
delete_from_chain(Var hash, int index, int subindex, int lastentry)
{
	/* delete... and try to optimize list stuff */
	if (subindex == 1 && lastentry == 2) {
		/* first and last */
		listset(hash, zero, index);
	} else if (subindex == 1) {
		/* first */
		hash.v.list[index] = subchain(hash.v.list[index], subindex+2, lastentry);
	} else if (subindex+1 == lastentry) {
		/* last */
		hash.v.list[index] = subchain(hash.v.list[index], 1, subindex - 1);
	} else {
		/* middle */
		Var oldv, newv;
		int j, newj;

		oldv = hash.v.list[index];
		newv = new_list(lastentry - 2);
		for (j = 1; j <= lastentry; j++) {
		    if (j == subindex || j == subindex + 1) {
			continue;
		    }
		    newj = (j >= subindex + 1) ? j - 2 : j;
		    newv.v.list[newj] = var_ref(oldv.v.list[j]);
		}
		free_var(oldv);
		hash.v.list[index] = newv;
	}
}

static Var
hashdel(Var hash, Var key)
{
	int index;

	index = index_for(hash, key);

	if (hash.v.list[index].type != TYPE_LIST) {
		/* well, it ain't here, boss */
		return hash;
	} else {
		int subindex, lastentry;
		lastentry = hash.v.list[index].v.list[0].v.num;
		
		for (subindex = 1; subindex <= lastentry; subindex += 2) {
			if (equality(hash.v.list[index].v.list[subindex], key, 1)) {
				delete_from_chain(hash, index, subindex, lastentry);				
				dec_keycount(hash);
				return hash;
			}
		}
	}

	/* nothin' */
	return hash;
}

static Var
_do_hash_resize(Var old, int newsize)
{
	int i;
	Var entry;
	
	Var new = alloc_list_for_hash(newsize + HASH_RESERVED);
	if (new.v.list[0].v.num == 0) {
		panic("Got 0-length list from alloc_list_for_hash!");
	}

	/* zero it out */
	for (i = HASH_START; i <= hash_end(new); i++) {
		new.v.list[i] = zero;
	}
	/* aaand the keycount */
	new.v.list[1] = zero;

	/* so now, all oldhash items have a new index. */
	for (i = HASH_START; i <= hash_end(old); i++) {
		entry = old.v.list[i];
		if (entry.type != TYPE_LIST)
			continue;
		
		int subindex;
		
		for (subindex = 1; subindex <= entry.v.list[0].v.num; subindex += 2)
			new = hashset(new, var_ref(entry.v.list[subindex]), var_ref(entry.v.list[subindex+1]));
	}
	
	/* and we're all done. chuck the old one. */
	free_var(old);
	return new;
}

static Var
hashexpand_in_advance(Var hash, int keys_to_add)
{
	int limit;
	
	if (hash_slots(hash) < 1 || keycount(hash) < 0) {
		errlog("Got %i hash_slots, %i keycount hash in hashexpand_in_advance\n", hash_slots(hash), keycount(hash));
		panic("Can't continue with broken hash");
	}
	
	limit = (hash_slots(hash) >> 2) + (hash_slots(hash) >> 1);
	
	/* this is fastmath for (keycount >= current_size * 3/4) */
	if (keycount(hash) >= limit) {
		return hashexpand(hash);
	} else {
		return hash;
	}
}

static Var
hashexpand(Var old)
{
	if (hash_slots(old) == hashsize(31)) {
		Var e;
		e.type = TYPE_ERR;
		e.v.err = E_QUOTA;
		errlog("hash was at size %d -- can't expand.\n", hash_slots(old));
		free_var(old);
		
		return e;
	} else {
		/* bigger! */
		return _do_hash_resize(old, hash_slots(old) << 1);
	}
}

static Var
optimize_hash(Var hash)
{
	int newsize;
	Var new = var_ref(hash);
	
	newsize = hash_slots(hash) >> 1;
	
	while (keycount(hash) <= newsize && newsize >= INITIAL_HASH_SIZE) {
		new = _do_hash_resize(new, newsize);
		newsize = newsize >> 1;
	}
	
	free_var(hash);
	return new;
}


static Var
_hash_keys_or_values(Var hash, int get_values)
{
	int i, keynum;
	Var list, entry;
	
	list = new_list(keycount(hash));
	keynum = 1;
	
	for (i = HASH_START; i <= hash_end(hash); i++) {
		entry = hash.v.list[i];
		if (entry.type != TYPE_LIST)
			continue;
		
		int subindex;
		
		for (subindex = 1; subindex <= entry.v.list[0].v.num; subindex += 2)
			list.v.list[keynum++] = var_ref(entry.v.list[subindex + get_values]);
	}
	
	return list;
}

Var
hashkeys(Var hash)
{
	return _hash_keys_or_values(hash,0);
}

Var
hashvalues(Var hash)
{
	return _hash_keys_or_values(hash,1);
}

static package
bf_hash(Var arglist, Byte next, void *vdata, Objid progr)
{
    int i;
    Var r, entry;
    r = new_hash();

    for (i = 1; i <= arglist.v.list[0].v.num; i++) {
	entry = arglist.v.list[i];
	if (entry.type != TYPE_LIST) {
		free_var(arglist);
		free_var(r);
		return make_error_pack(E_TYPE);
	}
	if (entry.v.list[0].v.num != 2) {
		free_var(arglist);
		free_var(r);
		return make_error_pack(E_ARGS);
	}
	if (entry.v.list[1].type != TYPE_STR && entry.v.list[1].type != TYPE_ERR
	    && entry.v.list[1].type != TYPE_OBJ && entry.v.list[1].type != TYPE_FLOAT
	    && entry.v.list[1].type != TYPE_INT) {
		free_var(arglist);
		free_var(r);
		return make_error_pack(E_TYPE);
	}
	r = hashset(r, var_ref(entry.v.list[1]), var_ref(entry.v.list[2]));
	
	if (r.type == TYPE_ERR) {
		free_var(arglist);
		return make_error_pack(r.v.err);
	}
    }

    free_var(arglist);
    return make_var_pack(r);
}


static package
bf_hashremove(Var arglist, Byte next, void *vdata, Objid progr)
{
    Var r, hash;

    switch (arglist.v.list[2].type) {
	case TYPE_STR:
	case TYPE_INT:
	case TYPE_FLOAT:
	case TYPE_OBJ:
	case TYPE_ERR:
		hash = arglist.v.list[1];
		
		if (var_refcount(hash) == 1)
			r = var_ref(hash);
	    	else {
			r = var_dup(hash);
		}

		r = hashdel(r, var_ref(arglist.v.list[2]));
		break;
	default:
		free_var(arglist);
		return make_error_pack(E_TYPE);
		break;
    }

    free_var(arglist);
    return make_var_pack(r);	
}

static package
bf_optimize(Var arglist, Byte next, void *vdata, Objid progr)
{
    Var r;
    r = optimize_hash(var_ref(arglist.v.list[1]));
    free_var(arglist);
    return make_var_pack(r);	
}

static package
bf_keys(Var arglist, Byte next, void *vdata, Objid progr)
{
    Var r;
    r = hashkeys(arglist.v.list[1]);
    free_var(arglist);
    return make_var_pack(r);	
}

static package
bf_values(Var arglist, Byte next, void *vdata, Objid progr)
{
    Var r;
    r = hashvalues(arglist.v.list[1]);
    free_var(arglist);
    return make_var_pack(r);
}

void
register_hash(void)
{
    register_function("hash", 0, -1, bf_hash);
    register_function("hashremove", 2, 2, bf_hashremove, TYPE_HASH, TYPE_ANY);
    register_function("optimize", 1, 1, bf_optimize, TYPE_HASH);
    register_function("keys", 1, 1, bf_keys, TYPE_HASH);
    register_function("values", 1, 1, bf_values, TYPE_HASH);
}

char rcsid_hash[] = "$Id: hash.c,v 1.8 2009/10/11 18:31:46 blacklite Exp $";

/* 
 * $Log: hash.c,v $
 * Revision 1.8  2009/10/11 18:31:46  blacklite
 * remove unused newsize
 *
 * Revision 1.7  2009/10/11 00:29:35  blacklite
 * don't add old keycount to new keycount during expansion (cvs diff -u hash.h),
 *
 * Revision 1.6  2009/08/14 21:34:39  blacklite
 * replace abort() with proper panic()s in hash verbs
 *
 * Revision 1.5  2009/08/14 16:38:03  blacklite
 * fix horrible has bugs! use the return value from hashset! i am dumb!
 *
 * Revision 1.4  2009/07/23 04:27:26  blacklite
 * fix freeing in hashset
 * someday I will quit making stupid free_var/var_ref errors
 *
 * Revision 1.3  2009/07/22 19:27:09  blacklite
 * Fixed bug where a dup'd hash pointed to old hashes' keys/values.
 *
 * Revision 1.2  2009/03/27 18:49:45  blacklite
 * fix memory alloc type so that M_HASH allocations are properly counted
 *
 */
