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
#define CONNPORT "22000"
#define CONNMAX 1000
#define CONNBACKLOG 1000


int listenfd;
int clients[CONNMAX];

void startServer();


int main()
{
	char str[100]; 
	struct sockaddr_in clientaddr;
	socklen_t addrlen;
	int slot = 0;

	int i;
	for (i=0; i<CONNMAX; i++)
		clients[i] = -1;

	/* CONFIGURE SERVER */
	startServer();

	/* ACCEPT CONNECTIONS */
	while (1)
	{
		// System call extracts the 1st connection request on queue of pending
		// connections (CONNBACKLOG) for listening socket and creates a new
		// connected socket, returning a file descriptor refereing to that 
		// socket.
		addrlen = sizeof(clientaddr);
		clients[slot] = accept(listenfd, (struct sockaddr *)&clientaddr, &addrlen);
			
		// Error accepting connection.
		if (clients[slot] < 0)
		{
			fprintf(stderr, "Error accepting request. %s\n", getError(errno));
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
				client_status = checkSocket(clients[slot]);
				if (client_status < 1)
					break;

				bzero(str, 100);
				read(clients[slot], str, 100);

				fprintf(stdout, "Echoing back: %s\n", str);

				write(clients[slot], str, strlen(str)+1);
			}
		}
		closeSocket(clients[slot]);
	}

	shutdown(listenfd, SHUT_RDWR);
	close(listenfd);
	exit(0);
}



void startServer() 
{
	int status;
	char port[6];
	strcpy(port, CONNPORT);
	struct addrinfo hints, *res, *p;
	
	// getaddrinfo for host.
	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	status = getaddrinfo(NULL, port, &hints, &res);
	if (status != 0)
	{
		fprintf(stderr, "Error in getaddrinfo. %s\n", getError(errno));
		exit(1);
	}

	// Bind a socket.
	for (p=res; p!=NULL; p=p->ai_next)
	{
		// Creates and endpoint for communication and return a file descriptor.     
		// The first argument specifies the communication domain; selects the 
		// protocol family to be used.                                           
		listenfd = socket(p->ai_family, p->ai_socktype, 0);                           
		if (listenfd < 0)                                                          
		{                                                                           
			fprintf(stderr, "Error creating a socket. %s\n", getError(errno));      
			continue;                        
		}
		// Bind a name to a socket. Assign the address specified by servaddr to 
		// socket refered by file descriptor listenfd.                                                    
		status = bind(listenfd, p->ai_addr, p->ai_addrlen);  
		if (status == 0)
			break;
	}
	if (p==NULL)
	{
		fprintf(stderr, "Error creating or binding address to socket. %s\n", getError(errno));
		exit(-1);                                                               
	}

	// Free the dynamically allocated linked list res.
	freeaddrinfo(res);

	// Listen for connections on a socket.
	// Mark the socket lsiten_fd as a passive socket (accept incoming 
	// connection requests).                                                           
	status = listen(listenfd, CONNBACKLOG);
	if (status < 0)
	{
		fprintf(stderr, "Error while marking listenfd as passive socket. %s\n", getError(errno));
		exit(-1);
	}
}
