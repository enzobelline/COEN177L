# Name: Laurence Kim
# Date: 01/28/2022
# Title: Lab3.5
# Description: This program the producer send a message to memory and then the consumer reads it
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/errno.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>

int main() {
	key_t sharedKey;
	int queue = msgget(sharedKey, IPC_CREAT | 0644);
        char * sharedBuffer = (char *) shmat(sharedMemory, 0, 0);	
	int sharedMemory = shmget(sharedKey, 1024, IPC_CREAT | 0666);

	//PRODUCER
	if (fork() == 0){ 
		const char *message = "COEN177WINTER2022";	
		strncpy(sharedBuffer, message, strlen(message));

		/* Data is ready. */
		int msgp = 1;
		int msgsnd_return = msgsnd(queue, &msgp, sizeof(msgp), IPC_NOWAIT);
		
		if (msgsnd_return == 0) {
			printf("ProducerMessage. Message: %s \n", message);
		}
		else {
			printf("ERROR: %d\n", errno);
		}
	}
	//CONSUMER
	else if (fork()==0){
		/* Check message status. */
		int message_status = msgrcv(queue, NULL, 0, 0, 0);
		
		/* Read buffer. */
		char message[128];
		strncpy(message, sharedBuffer, sizeof(message));
		
		printf("ConsumerMessage. Message: %s \n", message);
	}
	wait(0);
	wait(0); 
	return 0;
}


