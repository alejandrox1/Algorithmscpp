#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <arpa/inet.h>
#include <stdio.h>
#include "utilities.h"


#define BUFFSIZE 100


void echoClient(int *sockfd)
{
	char buff[100];
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


void sendFile(int *sockfd)
{
	int commfd = *sockfd;
	char buff[BUFFSIZE];
	FILE *file = fopen("sent.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error opening file");
		return;
	}
	while (!feof(file))
	{
		int rval = fread(buff, 1, sizeof(buff), file);
		send(commfd, buff, rval, 0);
	}
}



#endif // __OPERATIONS_H__
