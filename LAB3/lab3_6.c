# Name: Laurence Kim
# Date: 01/28/2022
# Title: Lab3.6
# Description: This program creates threads and then prints them
/**************************
*       COEN177: Threads  *
**************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//The code creates threads and prints the thread # and its corresponding data 
void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, &i);
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


