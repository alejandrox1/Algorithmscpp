#ifndef __CLIENTOPS_H__
#define __CLIENTOPS_H__

#include <unistd.h>

#define BUFFSIZE 100

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


#endif // __CLIENTOPS_H__
