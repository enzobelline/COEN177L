// Name: Laurence Kim 
// Date:  01/26/22
// Title: Lab2.7
// Description: Program creates child that runs ls command to which the parent waits thens exits.

#include <stdio.h>     
#include <sys/types.h>  
#include <unistd.h>     
#include <stdlib.h>
#include <errno.h>    

int main(int argc, char *argv[]) {
    pid_t  pid;
    int i;
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }    
    else if(pid == 0)
    {
        execlp("/bin/ls", "ls", NULL);
    }
    else
    {
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }
 
    return 0;
}

