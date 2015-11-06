#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "reader.h"
#include "writer.h"
#include "common.h"

#define NUM_THREADS 15

//the semaphores
sem_t mutex, wrt;

//the shared data
struct shared_data_info shared;

//the number of readers
int readcount;

//initialize the count of each semaphore
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
	
	//set up the two types of threads
	pthread_t readerThread;
	pthread_t writerThread;
	pthread_attr_t attr;
	void *status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	initialize_semaphores();

	//set up the shared data
	struct shared_data_info shared = {
		.mutex = &mutex,
		.wrt = &wrt,
		.readcount = &readcount
	};

	//see rand
	srand(time(NULL));
	int a;

	//keep track of how many readers and writers have been spawned
	int writersspawned;
	int readersspawned;
	writersspawned = 0;
	readersspawned = 0;

	int i;
	//make all the threads
	for (i = 0; i < NUM_THREADS; i++) {
		a = rand();
		//randomly generate either a reader or writer
		if (a % 2) {
			//make a reader
			if (pthread_create(&readerThread, &attr, reader, (void *)&shared) == -1){
				perror("pthread_create(readerThread)");
				exit(EXIT_FAILURE);
			}
			//keep track of readers made
			readersspawned++;
		} else {
			//writer
			if (pthread_create(&writerThread, &attr, writer, (void *)&shared) == -1){
				perror("pthread_create(writerThread)");
				exit(EXIT_FAILURE);
			}
			//keep track of writers made
			writersspawned++;
		}
	}

	int j;
	int k;

	//tell parent thread to wait on the readers
	for (j = 0; j < readersspawned; j++) {
		if (pthread_join(readerThread, &status) == -1) {
			perror("pthread_join(readerThread)");
			exit(EXIT_FAILURE);
		}
	}

	//tell parent to wait on writers
	for (k = 0; k < writersspawned; k++) {
		if (pthread_join(writerThread, &status) == -1) {
			perror("pthread_join(writerThread)");
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;

}
