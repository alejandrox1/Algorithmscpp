#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <unistd.h>                                                             
#include <time.h>
                                                      
                                                                                
int createDevUrandomFile(const char *filename)                                                                      
{                                                                               
    srand(time(NULL));    
                                                        
    int mult=1;                                                                 
    int i;                                                                      
    for (i=0; i<30; i++)                                                        
    {                                                                           
        mult = rand()%10 + 1;                                                   
        printf("%d ", mult);                                                    
    }                                                                           
    printf("\n");                                                               
    printf("mult = %d\n", mult);                                                
                                                                                
    size_t n;                                                                   
    char buf[1024*1024];                                                        
    FILE *input, *output;                                                       
    input = fopen("/dev/urandom", "r");                                         
    output = fopen(filename, "w");                                           
    for (i=0; i<mult; i++)                                                      
    {                                                                           
        n = fread(buf, 1, sizeof(buf), input);                                  
        if (n < 1024)                                                           
            fprintf(stderr, "error reading from file\n");                       
                                                                                
        n = fwrite(buf, 1, sizeof(buf), output);                                
        if (n < 1)                                                              
            fprintf(stderr, "cannot write to file\n");                          
    }                                                                           
    fclose(input);                                                              
    fclose(output);                                                             
                                                                                
    exit(0);                                                                    
}  

#endif // __FILEUTILS_H__
