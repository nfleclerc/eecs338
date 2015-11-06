#ifndef SEMAPHORE_COMMON
#define SEMAPHORE_COMMON

#include <semaphore.h>

//the shared data
struct shared_data_info {
	//the two semaphores
	sem_t *mutex;
	sem_t *wrt;
	//the number of readers that are going
	int *readcount;
};

#endif
