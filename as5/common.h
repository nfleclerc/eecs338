#ifndef SEMAPHORE_COMMON
#define SEMAPHORE_COMMON

#include <semaphore.h>

struct shared_data_info {
	sem_t *mutex;
	sem_t *wrt;
	int readcount;
};

#endif
