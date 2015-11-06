#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"
#include <time.h>

void *writer(void *shared_data) {
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;

	//wait(wrt)
	if (sem_wait(shared->wrt) == -1){
		perror("wait(wrt)");
		pthread_exit(NULL);
	}

	printf("%lu: Waiting on wrt semaphore...\n", (unsigned long)pthread_self());
	fflush(0);
	sleep (1);

	//in critical section

	printf("%lu: Writing the next Shakespearean play... \n", (unsigned long)pthread_self());
	fflush(0);
	nanosleep((const struct timespec[]){{2, 0}}, NULL);

	//crit section end

	//signal(wrt)
	if (sem_post(shared->wrt) == -1){
		perror("signal(wrt)");

		pthread_exit(NULL);
	}
	printf("%lu: Signaling the wrt semaphore...\n", (unsigned long)pthread_self());
	fflush(0);
	nanosleep((const struct timespec[]){{2, 0}}, NULL);

	pthread_exit(NULL);

}
