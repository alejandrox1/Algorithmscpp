#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdio.h>
#include "utilities.h"

#define BUFFSIZE 1024


// echoClient is an operation that will respond to a client by echoing back its
// message.
void echoClient(int *sockfd)
{
	char buff[BUFFSIZE];
	char ip[INET6_ADDRSTRLEN];
	int client_status, commfd = *sockfd;      

	bzero(ip, sizeof(ip));
	getClientIP(commfd, ip, INET6_ADDRSTRLEN);

	while (1)                                                           
	{                                                                   
		client_status = checkSocket(commfd);                     
		if (client_status < 1)
		{
			fprintf(stdout, "Connection %s broken\n", ip);
			break;     
		}
                                                                                
		bzero(buff, BUFFSIZE);                                                
		read(commfd, buff, BUFFSIZE);                                  
		fprintf(stdout, "Echoing back: %s", buff);                     
		write(commfd, buff, strlen(buff)+1);                       
	}
}


// sendFile sends contents from buf to socket.
int sendFile(int sockfd, const void * buf, int len)
{
	const char *pbuf = (const char *)buf;
	while (len > 0)
	{
		int sent = send(sockfd, pbuf, len, 0);
		if (sent < 1)
		{
			fprintf(stderr, "cannot write to socket");
			return -1;
		}

		// server.
		fprintf(stdout, "sent %d: '%s' with len: %d\n", sent, pbuf, len);
		pbuf += sent;
		len -= sent;
	}
	return 0;
}

// serverSendFile will send the contents of a file over to a socket.
// It utilizes the function sendFile.
void serverSendFile(int sockfd)
{
	const char* filename = "sent.txt";
	char buff[BUFFSIZE];
	struct stat s;

	if (stat(filename, &s) < 0)
	{
		fprintf(stderr, "Cannot stat file\n");
		return;
	}

	FILE *file = fopen(filename, "rb");
	if (file == NULL)                                                           
    {                                                                           
        fprintf(stderr, "Error opening file");                                  
        return;                                                                 
    }	

	long size = s.st_size;
	long tmpSize = htonl(size);
	// Send file size.
	if (sendFile(sockfd, &tmpSize, sizeof(tmpSize)) == 0)
	{
		while (size > 0)
		{
			int n = fread(buff, 1, MIN(sizeof(buff), size), file);
			if (n < 1)
			{
				fprintf(stderr, "cannot read from file\n");
				break;
			}
			
			fprintf(stdout, "sending: '%s'\n", buff);
			if (sendFile(sockfd, buff, n) < 0)
				break;

			size -= n;
		}
	}
	fclose(file);
}


#endif // __OPERATIONS_H__
