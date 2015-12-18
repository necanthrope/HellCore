/******************************************************************************
  2009 The Hell Syndicate.

  Rights considered an annoyance of oppressive litigious society and 
  neither reserved nor recognized. Besides, how did you get this code?
 *****************************************************************************/


/*
 * It's mysql from inside moo!
 */

#ifdef MOOMYSQL
#ifndef MOOMYSQL_H

#include "structures.h"

typedef int moomysql_handle;

moomysql_handle
moomysql_open_connection(const char *host, const char *user,
	const char *passwd, const char *db, unsigned int port, const char *unix_socket);

void moomysql_close_connection(moomysql_handle h);

Var moomysql_error(moomysql_handle h);

Var moomysql_send_query(moomysql_handle h, const char *query);

Var moomysql_next_row(moomysql_handle h);

void moomysql_close_all_connections(void);

#define MOOMYSQL_H
#endif
#endif

