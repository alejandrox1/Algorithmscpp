#ifndef __CLIENTOPS_H__
#define __CLIENTOPS_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>


#define BUFFSIZE 1024


void sendString(int sockfd)                                                
{                                                                               
    char sendline[BUFFSIZE];                                                         
    char recvline[BUFFSIZE];                                                         
    
	while (1)                                                                   
    {                                                                           
        bzero(sendline, BUFFSIZE);                                                   
        bzero(recvline, BUFFSIZE);

        fgets(sendline, BUFFSIZE, stdin);                                                                                                                    
        write(sockfd, sendline, strlen(sendline)+1);                            
        read(sockfd, recvline, BUFFSIZE);                                            
        
		printf("received: %s\n", recvline);                                        
    }                           
} 

int writeFile(FILE *file, const void *buff, int len)
{
	const char *pbuff = (const char *)buff;

	while (len > 0)
	{
		int written = fwrite(pbuff, 1, len, file);
		if (written < 1)
		{
			fprintf(stderr, "cannot write to file\n");
			return -1;
		}
		pbuff += written;
		len -= written;
	}
	return 0;
}


int readFile(int sockfd, void *buff, int len)
{
	char *pbuff = (char *)buff;
	int total = 0;

	while (len > 0)
	{
		int n = recv(sockfd, pbuff, len, 0);
		if (n < 0)
		{
			fprintf(stderr, "cannot read from socket\n");
			return -1;
		}
		if (n == 0)
		{
			fprintf(stderr, "socket disconnected");
			return 0;
		}

		pbuff += n;
		len -= n;
		total += n;
	}
	return total;
}

void recvFile(int sockfd)
{
	char buff[BUFFSIZE];
	FILE *file = fopen("recv.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error opening file");
		return;                                                                 
	}

	int n;
	long size = 0;
	if (readFile(sockfd, &size, sizeof(size)) == 1)
	{
		size = ntohl(size);
		while (size > 0)
		{
			n = readFile(sockfd, buff, MIN(sizeof(buff), size));
			if (n < 1)
				break;
			if (writeFile(file, buff, n) == -1)
				break;
		}
	}
	fclose(file);
}

#endif // __CLIENTOPS_H__
