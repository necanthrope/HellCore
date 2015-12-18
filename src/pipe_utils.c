
#include "my-stdlib.h"
#include "my-unistd.h"

#include "my-wait.h"
#include <errno.h>

#include "log.h"
#include "storage.h"

/******************************************************************************
 * Utilities
 *****************************************************************************/
		
pid_t
spawn_pipe(void (*child_proc) (int to_parent, int from_parent),
		   int *to_child, int *from_child)
{	   
	int pipe_to_child[2], pipe_from_child[2];
	pid_t pid;
			
	if (pipe(pipe_to_child) < 0) {
		log_perror("SPAWNING: Couldn't create first pipe");
	} else if (pipe(pipe_from_child) < 0) {
		log_perror("SPAWNING: Couldn't create second pipe");
		close(pipe_to_child[0]);
		close(pipe_to_child[1]);
	} else if ((pid = fork()) < 0) {
		log_perror("SPAWNING: Couldn't fork middleman");
		close(pipe_to_child[0]);
		close(pipe_to_child[1]);
		close(pipe_from_child[0]);
		close(pipe_from_child[1]);
	} else if (pid != 0) {	  /* parent */
		int status;

		close(pipe_to_child[0]);
		close(pipe_from_child[1]);
		*to_child = pipe_to_child[1];
		*from_child = pipe_from_child[0];

		/* Cast to (void *) to avoid warnings on systems that misdeclare the
		 * argument.
		 */
		wait((void *) &status); /* wait for middleman to die */
		if (status != 0) {
			errlog("SPAWNING: Middleman died with status %d!\n", status);
			close(pipe_to_child[1]);
			close(pipe_from_child[0]);
		} else if (read(*from_child, &pid, sizeof(pid)) != sizeof(pid)) {
			errlog("SPAWNING: Bad read() for pid\n");
			close(pipe_to_child[1]);
			close(pipe_from_child[0]);
		} else {
			return pid;
		}
	} else {					/* middleman */
		close(pipe_to_child[1]);
		close(pipe_from_child[0]);
		if ((pid = fork()) < 0) {
			log_perror("SPAWNING: Couldn't fork child");
			exit(1);
		} else if (pid != 0) {  /* still the middleman */
			write(pipe_from_child[1], &pid, sizeof(pid));
			exit(0);			
		} else {				/* finally, the child */
			(*child_proc) (pipe_from_child[1], pipe_to_child[0]);
			exit(0);
		}
	}

	return 0;
}

void
ensure_buffer(char **buffer, int *buflen, int len)
{   
	if (len > *buflen) {
		if (*buffer)
			myfree(*buffer, M_STRING);
		*buflen = len;
		*buffer = mymalloc(len, M_STRING);
	}
}

int
robust_read(int fd, void *buffer, int len)
{
	int count;

	do {
		count = read(fd, buffer, len);
	} while (count == -1 && errno == EINTR);

	return count;
}



