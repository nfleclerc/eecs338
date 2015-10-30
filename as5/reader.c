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

	shared->readcount = shared->readcount + 1;
	if (shared->readcount == 1){
		if (sem_wait(shared->wrt) == -1) {
			perror("wait(wrt)");
			pthread_exit(NULL);
		}
	}

	if (sem_post(shared->mutex) == -1) {
		perror("signal(mutex)");
		pthread_exit(NULL);
	}

	//critical section start

	printf("Reading... \n");
	fflush(0);

	//critical section end

	if (sem_wait(shared->mutex) == -1) {
		perror("wait(mutex)");
		pthread_exit(NULL);
	}

	shared->readcount = shared->readcount - 1;
	if (shared->readcount == 0){
		if (sem_post(shared->wrt) == -1) {
			perror("signal(wrt)");
			pthread_exit(NULL);
		}
	}

	if (sem_post(shared->mutex) == -1) {
		perror("signal(mutex)");
		pthread_exit(NULL);
	}

	pthread_exit(NULL);

}
