#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"

void *writer(void *shared_data) {
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;

	//wait(wrt)
	if (sem_wait(shared->wrt) == -1){
		perror("wait(wrt)");
		pthread_exit(NULL);
	}

	//in critical section

	printf("Writing the next Shakespearean play... \n");
	fflush(0);

	//crit section end

	//signal(wrt)
	if (sem_post(shared->wrt) == -1){
		perror("signal(wrt)");

		pthread_exit(NULL);
	}

	pthread_exit(NULL);

}
