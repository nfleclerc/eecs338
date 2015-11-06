#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"
#include <time.h>

//control the reader thread
void *reader(void *shared_data) {
	
	//set up the shared data
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;

	//wait(mutex)
	if (sem_wait(shared->mutex) == -1) {
		perror("wait(mutex)");
		pthread_exit(NULL);
	}

	//print message that we are waiting and sleep
	printf("%lu: Waiting on mutex\n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() error");
		pthread_exit(NULL);
	}

	//increment the number of readers
	shared->readcount = shared->readcount + 1;

	//print message that the readcount is being incremented and sleep
	printf("%lu: Incrementing readcount\n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() error");
		pthread_exit(NULL);
	}

	//if the readcount = 1
	if (shared->readcount == (int *)1){
		
		//tell the wrt semaphore to wait
		if (sem_wait(shared->wrt) == -1) {
			perror("wait(wrt)");
			pthread_exit(NULL);
		}
		//print message and sleep
		printf("%lu: Reader reading. Writers waiting.\n", (unsigned long)pthread_self());
		fflush(0);
		if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
			perror("nanosleep() error");
			pthread_exit(NULL);
		}
	}

	//signal mutex
	if (sem_post(shared->mutex) == -1) {
		perror("signal(mutex)");
		pthread_exit(NULL);
	}
	//print that mutex is being signaled
	printf("%lu: Signaling mutex\n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() error");
		pthread_exit(NULL);
	}

	//critical section start

	//reader is reading
	printf("%lu: Reading... \n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() error");
		pthread_exit(NULL);
	}

	//critical section end

	//tell mutex to wait
	if (sem_wait(shared->mutex) == -1) {
		perror("wait(mutex)");
		pthread_exit(NULL);
	}

	//print message
	printf("%lu: Waiting on mutex\n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() error");
		pthread_exit(NULL);
	}

	//decrement readcount
	shared->readcount = shared->readcount - 1;

	//print message
	printf("%lu: Decrementing readcount\n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() error");
		pthread_exit(NULL);
	}

	//if readcount = 0
	if (shared->readcount == (int *)0){
		//signal wrt
		if (sem_post(shared->wrt) == -1) {
			perror("signal(wrt)");
			pthread_exit(NULL);
		}
		printf("%lu: No readers arriving. Signaling Writers.\n", (unsigned long)pthread_self());
		fflush(0);
		if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
			perror("nanosleep() error");
			pthread_exit(NULL);
		}
	}

	//signal the mutex
	if (sem_post(shared->mutex) == -1) {
		perror("signal(mutex)");
		pthread_exit(NULL);
	}

	//print message and sleep
	printf("%lu: Signaling mutex\n", (unsigned long)pthread_self());
	fflush(0);
	if (nanosleep((const struct timespec[]){{1, 0}}, (struct timespec[]){{1, 0}}) == -1){
		perror("nanosleep() error");
		pthread_exit(NULL);
	}

	//exit
	pthread_exit(NULL);

}
