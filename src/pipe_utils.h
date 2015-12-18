/******************************************************************************
  Utilities for pipe communication between processes
  (split from name_lookup.c)
 *****************************************************************************/

#ifndef PIPE_UTILS_H
#define PIPE_UTILS_H 1

extern pid_t 
spawn_pipe(void (*child_proc) (int to_parent, int from_parent),
		   int *to_child, int *from_child);

extern void
ensure_buffer(char **buffer, int *buflen, int len);

extern int
robust_read(int fd, void *buffer, int len);

#endif

/* 
 * $Log: pipe_utils.h,v $
 * Revision 1.1  2010/05/16 02:39:23  blacklite
 * Break out some IPC stuff into pipe_utils.c, add var serialization, and some unfinished mysql stuff
 *
 *
 */
