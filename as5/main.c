#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "reader.h"
#include "writer.h"
#include "common.h"

#define NUM_FORKS 15

sem_t mutex, wrt;

struct shared_data_info shared;

int readcount;

void initialize_semaphores() {
	if (sem_init(&mutex, 0, 1) < 0) {
		perror("sem_init(&mutex)");
		exit(EXIT_FAILURE);
	}
	if (sem_init(&wrt, 0, 1) < 0) {
		perror("sem_init(&wrt)");
		exit(EXIT_FAILURE);
	}
}

int main() {
	
	pthread_t readerThread;
	pthread_t writerThread;
	pthread_attr_t attr;
	void *status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	initialize_semaphores();

	struct shared_data_info shared = {
		.mutex = &mutex,
		.wrt = &wrt,
		.readcount = &readcount
	};

	srand(time(NULL));
	int a;


	int writersspawned;
	int readersspawned;
	writersspawned = 0;
	readersspawned = 0;

	int i;
	for (i = 0; i < NUM_FORKS; i++) {
		a = rand();
		if (a % 2) {
			if (pthread_create(&readerThread, &attr, reader, (void *)&shared) == -1){
				perror("pthread_create(readerThread)");
				exit(EXIT_FAILURE);
			}
			readersspawned++;
		} else {
			//writer
			if (pthread_create(&writerThread, &attr, writer, (void *)&shared) == -1){
				perror("pthread_create(writerThread)");
				exit(EXIT_FAILURE);
			}
			writersspawned++;
		}
	}

	int j;
	int k;

	for (j = 0; j < readersspawned; j++) {
		if (pthread_join(readerThread, &status) == -1) {
			perror("pthread_join(readerThread)");
			exit(EXIT_FAILURE);
		}
	}

	for (k = 0; k < writersspawned; k++) {
		if (pthread_join(writerThread, &status) == -1) {
			perror("pthread_join(writerThread)");
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;

}
