// POSIX.1 does not require the inclusion of <sys/types.h>, and this header 
// file is not required on Linux.  However, some historical (BSD) 
// implementations required this header file, and portable applications are 
// probably wise to include it.
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "utilities.h"


#define BUFF_SIZE (1024*1024)
#define CONN_PORT 22000
#define CONN_BACKLOG 10


int main()
{
	int status;
	char str[100]; //*str = (char *)malloc(BUFF_SIZE); 		/* Allocate 1MB .*/
	int listen_fd, comm_fd;

	struct sockaddr_in servaddr;

	bzero(&servaddr, sizeof(servaddr));                                         
	servaddr.sin_family = AF_INET;                                              
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);                               
	servaddr.sin_port = htons(CONN_PORT);

	// Creates and endpoint for communication and return a file descriptor.
	// The first argument specifies the communication domain; selects
	// theprotocol family to be used. 
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
	{
		fprintf(stderr, "Error creating a socket. %s\n", get_error(errno));
		exit(-1);
	}

	// Bind a name to a socket. 
	// Assign the address specified by servaddr to socket refered by file 
	// descriptor listen_fd.
	status = bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (status < 0)
	{
		fprintf(stderr, "Error binding address to socket. %s\n", get_error(errno));
		exit(-1);
	}

	// Listen for connections on a socket.
	// Mark the socket lsiten_fd as a passive socket (accept incoming connection
	// requests)
	status = listen(listen_fd, CONN_BACKLOG);
	if (status < 0)
	{
		fprintf(stderr, "Error while marking listen_fd as passive socket. %s\n", get_error(errno));
		exit(-1);
	}

	/*	ACCEPT CONNECTIONS */
	while (1)
	{
		// System call extracts the 1st connection request on queue of pending
		// connections (CONN_BACKLOG) for listening socket and creates a new
		// connected socket, returning a file descriptor refereing to that 
		// socket.
		comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
			
		// Error accepting connection.
		if (comm_fd < 0)
		{
			fprintf(stderr, "Error accepting request. %s\n", get_error(errno));
			if((errno == ENETDOWN || errno == EPROTO || errno == ENOPROTOOPT || 
						errno == EHOSTDOWN || errno == ENONET || 
						errno == EHOSTUNREACH || errno == EOPNOTSUPP || 
						errno == ENETUNREACH)) 
			{
				continue;
			}
			exit(-1);
			
		}
		// Process client reuests.
		else 
		{
			int client_status;
			while (1)
			{
				client_status = check_client_connection(comm_fd);
				if (client_status < 1)
					break;

				bzero(str, 100);
				read(comm_fd, str, 100);

				fprintf(stdout, "Echoing back: %s\n", str);

				write(comm_fd, str, strlen(str)+1);
			}
		}
		close(comm_fd);
	}

	free(str);
	exit(0);
}
