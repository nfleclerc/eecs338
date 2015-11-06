#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"
#include <time.h>

//control of the writer thread
void *writer(void *shared_data) {
	
	//set up the shared data
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;

	//wait(wrt)
	if (sem_wait(shared->wrt) == -1){
		perror("wait(wrt)");
		pthread_exit(NULL);
	}

	//print message
	printf("%lu: Waiting on wrt semaphore...\n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() failed");
		pthread_exit(NULL);
	}

	//in critical section

	//writer is writing
	printf("%lu: Writing the next Shakespearean play... \n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() failed");
		pthread_exit(NULL);
	}
	//crit section end

	//signal(wrt)
	if (sem_post(shared->wrt) == -1){
		perror("signal(wrt)");

		pthread_exit(NULL);
	}
	//print message
	printf("%lu: Signaling the wrt semaphore...\n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() failed");
		pthread_exit(NULL);
	}

	//exit
	pthread_exit(NULL);

}
