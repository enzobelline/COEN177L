// Name: Laurence Kim 
// Date:  01/26/22
// Title: Lab2.5
// Description: Create seven processes with either two or zero children.
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    printf("Parent ID: %d \n", getppid());
    printf("Current ID: %d \n \n", getpid());

    /* Make one branch. */
    pid_t pid1 = fork();
    if (pid1 == -1) {
	fprintf(stderr, "can't fork, error %d\n", errno);
    }
    if (pid1 == 0) {
	pid_t pid11 = fork();
	if (pid11) {
	    pid_t pid12 = fork();
	    if (pid12) {
	        printf("Parent 1: %d ", getpid());
	        printf("Child 1: %d ", pid11);
	        printf("Child 2: %d \n", pid12);
	    }
	}
    }
    else {
	/* Make the other branch. */
	pid_t pid2 = fork();
	if (pid2 == -1) {
	    fprintf(stderr, "can't fork, error %d\n", errno);
	}
	if (pid2) {
	    printf("Parent 1: %d ", getpid());
    	    printf("Child 1: %d ", pid1);
    	    printf("Child 2: %d \n", pid2);
	}
	if (pid2 == 0) {
	    pid_t pid21 = fork();
	    if (pid21) {
		pid_t pid22 = fork();
		if (pid22) {
		    printf("Parent 1: %d ", getpid());
                    printf("Child 1: %d ", pid21);
                    printf("Child 2: %d \n", pid22);
		}
	    }
	}
    }
    wait();
    exit(0);
}
	    

