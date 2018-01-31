#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


// getError returns error message.
char* getError(int n)
{
	size_t size = 1024;
	char *buff = (char *) malloc(size);
	if (buff == NULL)
		return NULL;

	// TODO: better error handling here... 
	if (strerror_r(n, buff, size) < 0)
		return NULL;
	return buff;
}


// checkSocket is used to check whether a client is still connected and to
// clear out any errors before shutting down. 
int checkSocket(int socket_fd)
{
	int err = 0;
	socklen_t len = sizeof(err);
	int status;

	status = getsockopt(socket_fd, SOL_SOCKET, SO_ERROR, &err, &len);
	if (status != 0)
	{
		fprintf(stderr, "Error getting socket error code: %s\n", getError(status));
		return -1;
	}
	if (err != 0)
	{
		errno = err;
		fprintf(stdout, "socket error: %s\n", getError(err));
		return 0;
	}
	return 1;
}


// closeSocket will gracefully shut down and close a socket.
void closeSocket(int comm_fd)
{
	int status;
	if (comm_fd > 0)
	{
		// Clear errors to prevent close from failing.
		checkSocket(comm_fd);

		status = shutdown(comm_fd, SHUT_RDWR);
		if (status < 0)
			if (errno != ENOTCONN && errno != EINVAL)
				perror("shutting down client socket");
		
		status = close(comm_fd);
		if (status < 0)
			perror("closing client socket");
	}
}



#endif // __UTILITIES_H__
