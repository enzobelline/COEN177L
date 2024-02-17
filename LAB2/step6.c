// Name: Laurence Kim 
// Date:  01/26/22
// Title: Lab2.6
// Description: step1 with two threads vs two processes.

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h>    /* pthread */ 

void * secondThread(void * microseconds) {
    int i, n = *(int *)microseconds;
    for (i=0;i<100;i++) {
        printf("Second Thread %d\n",i);
        usleep(n);
    }
}


int main(int argc, char *argv[]) {
    int microseconds = atoi(argv[1]);
    int i, n = microseconds; 

    pthread_t thread_id;
    int thread = pthread_create(&thread_id, NULL, secondThread, &microseconds);

    for (i=0;i<100;i++) {
        printf("\t \t \t Main Thread %d \n",i);
        usleep(n);
    }

    if (thread) {
        fprintf(stderr, "error creating thread %d\n", errno);
    }

    pthread_join(thread_id, NULL);

    return 0;
}

