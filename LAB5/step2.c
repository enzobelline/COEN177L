// Name: Laurence Kim
// Date: 02/10/22 
// Title: Lab 5.2
// Description: Thread Synchronization baseline program with mutex locks modifications.

// Thread Sychronization
//To compile this code:
//If using the SCU Linux lab first add #include<fcntl.h>
//Then you're ready to compile.
//To compile just add -lpthread to your gcc command like:
//gcc threadSync.c -lpthread
//gcc threadSync.c -o test -lpthread

#include<fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 


#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock;

void* go(void* arg) { 
	pthread_mutex_lock(&lock);
	printf("Thread %d Entered Critical Section..\n", (intptr_t)arg); //critical section 
	sleep(1); 
	pthread_mutex_unlock(&lock);
	return (NULL);
} 

int main() { 
	pthread_mutex_init(&lock, NULL);
	static int i;
	for (i = 0; i < NTHREADS; i++)  
		pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
	for (i = 0; i < NTHREADS; i++) {
   		pthread_join(threads[i],NULL);
   		printf("\t\t\tThread %d returned \n", i);
   	}
	printf("Main thread done.\n");
	pthread_mutex_destroy(&lock);
	return 0; 
} 


