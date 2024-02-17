// Name: Laurence Kim
// Date: 02/10/22 
// Title: Lab 5.3
// Description: solves the producer - consumer problem using semaphores.
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>
#define NTHREADS 2
#define N 50
int buffer[N];
sem_t *full, *empty, *mutex;
pthread_t threads[NTHREADS];
void * consumer(void * arg) {
	int out = 0;
	int citem;
	while (1) {
		sem_wait(full);
		sem_wait(mutex);
		citem = buffer[out];
		out = (out + 1) % N;
		sem_post(mutex);
		sem_post(empty);
		printf("\t\tConsumed %d\n", citem);
		sleep(1);
	}
}
void * producer(void * arg) {
	srand(time(NULL));
	int in = 0;
	while(1) {
		int pitem = rand() % N;
		sem_wait(empty);
		sem_wait(mutex);
		buffer[in] = pitem;
		in = (in+1) % N;
		sem_post(mutex);
		sem_post(full);
		printf("Produced %d\n", pitem);
		sleep(1);
	}	 
}
int main() {
        full = sem_open("full", O_CREAT, 0644, 0);
        empty = sem_open("empty", O_CREAT, 0644, N);
        mutex = sem_open("mutex", O_CREAT, 0644, 1);
	
	pthread_create(&threads[0], NULL, producer, NULL);
	sleep(1);
	pthread_create(&threads[0], NULL, consumer, NULL);
	sleep(1);	

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	
	sem_unlink("full");
	sem_unlink("empty");
	sem_unlink("mutex");

	return 0; 
}

