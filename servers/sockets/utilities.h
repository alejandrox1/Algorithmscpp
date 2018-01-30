#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


char* get_error(int n)
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


int check_client_connection(int socket_fd)
{
	int error = 0;
	socklen_t len = sizeof(error);
	int status;

	status = getsockopt(socket_fd, SOL_SOCKET, SO_ERROR, &error, &len);
	if (status != 0)
	{
		fprintf(stderr, "Error getting socket error code: %s\n", get_error(status));
		return -1;
	}
	if (error != 0)
	{
		fprintf(stdout, "socket error: %s\n", get_error(error));
		return 0;
	}
	return 1;
}

#endif // __UTILITIES_H__
