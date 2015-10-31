#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"


void *reader(void *shared_data) {
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;

	//wait(mutex)

	if (sem_wait(shared->mutex) == -1) {
		perror("wait(mutex)");
		pthread_exit(NULL);
	}

	printf("%lu: Waiting on mutex\n", (unsigned long)pthread_self());
	fflush(0);
	sleep(1);

	shared->readcount = shared->readcount + 1;
	printf("%lu: Incrementing readcount\n", (unsigned long)pthread_self());
	fflush(0);
	sleep(1);

	if (shared->readcount == (int *)1){
		if (sem_wait(shared->wrt) == -1) {
			perror("wait(wrt)");
			pthread_exit(NULL);
		}
		printf("%lu: No readers arriving. Signaling Writers.\n", (unsigned long)pthread_self());
		fflush(0);
		sleep(1);
	}

	if (sem_post(shared->mutex) == -1) {
		perror("signal(mutex)");
		pthread_exit(NULL);
	}
	printf("%lu: Signaling mutex\n", (unsigned long)pthread_self());
	fflush(0);
	sleep(1);

	//critical section start

	printf("%lu: Reading... \n", (unsigned long)pthread_self());
	fflush(0);
	sleep(1);

	//critical section end

	if (sem_wait(shared->mutex) == -1) {
		perror("wait(mutex)");
		pthread_exit(NULL);
	}

	printf("%lu: Waiting on mutex\n", (unsigned long)pthread_self());
	fflush(0);
	sleep(1);

	shared->readcount = shared->readcount - 1;
	printf("%lu: Decrementing readcount\n", (unsigned long)pthread_self());
	fflush(0);
	sleep(1);

	if (shared->readcount == (int *)0){
		if (sem_post(shared->wrt) == -1) {
			perror("signal(wrt)");
			pthread_exit(NULL);
		}
		printf("%lu: No readers arriving. Signaling Writers.\n", (unsigned long)pthread_self());
		fflush(0);
		sleep(1);
	}

	if (sem_post(shared->mutex) == -1) {
		perror("signal(mutex)");
		pthread_exit(NULL);
	}

	printf("%lu: Signaling mutex\n", (unsigned long)pthread_self());
	fflush(0);
	sleep(1);

	pthread_exit(NULL);

}
