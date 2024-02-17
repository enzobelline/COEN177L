// Name: Laurence Kim
// Date: 02/10/22 
// Title: Lab 5.4
// Description: solves the producer - consumer problem using condition variables.
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define NTHREADS 2
#define N 50
pthread_t threads[NTHREADS];
pthread_cond_t full;
pthread_cond_t empty;
pthread_mutex_t mutex;
int currentElement = 0;
int buffer[N];
void * producer(void * arg) {
	srand(time(NULL));
	while(1) {
		int pitem = rand() % N;
		pthread_mutex_lock(&mutex);
		currentElement++;
		while(currentElement >= (N - 1)) {
			pthread_cond_wait(&empty, &mutex);
		}
		buffer[currentElement] = pitem;
		
		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
		printf("Produced %d\n", pitem);
		sleep(1);
	}	 
}
void * consumer(void * arg) {
	int citem;
	while (1) {
		pthread_mutex_lock(&mutex);
		while(currentElement < 0) {
			pthread_cond_wait(&full, &mutex);
		} 
		citem = buffer[currentElement--];
		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex);
		printf("\t\tConsumed %d\n", citem);
		sleep(1);
	}
}
int main() {
	pthread_mutex_init(&mutex, NULL);
	
	pthread_create(&threads[0], NULL, producer, NULL);
	sleep(1);
	pthread_create(&threads[0], NULL, consumer, NULL);
	sleep(1);	

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	
	pthread_mutex_destroy(&mutex);	

	return 0; 
}

