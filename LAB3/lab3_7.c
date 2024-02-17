# Name: Laurence Kim
# Date: 01/28/2022
# Title: Lab3.7
# Description: This program creates threads prints them but in order as the threads are now given a counter argument
/**************************
*       COEN177: Threads  *
**************************/
// Description: fixes counter by giving each thread's argument its own memory.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int numbers[NTHREADS];
    int i;
    for (i = 0; i < NTHREADS; i++) {
	numbers[i] = i; 
        pthread_create(&threads[i], NULL, go, &numbers[i]);
    }
    for (i = 0; i < NTHREADS; i++) {
    printf("Thread #%d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
 printf("Thread #%d Iteration %d\n",  (int)pthread_self(), *(int *)arg);
 return 0;
}


