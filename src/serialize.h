/******************************************************************************
  (De)serialization -- moo vars to null-terminated strings and vice versa.
 *****************************************************************************/

#ifndef SERIALIZE_H
#define SERIALIZE_H 1

#include "structures.h"

Var deserialize(const char *s);

char * serialize(Var v);

#endif

/* 
 * $Log: serialize.h,v $
 * Revision 1.1  2010/05/16 02:39:23  blacklite
 * Break out some IPC stuff into pipe_utils.c, add var serialization, and some unfinished mysql stuff
 *
 *
 */
