#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"

void tina(void *shared_data){
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;
	
	while (shared->cookiecount != 0){
		
		if (sem_wait(shared->mutex) == -1){
			perror("wait(mutex)");
			exit(EXIT_SUCCESS);
		}
		
		// critical section start
		
		shared->cookiecount = shared->cookiecount - 1;
		shared->tinacount = shared->tinacount + 1;
		
		//critical section end
		
		if (sem_post(shared->mutex) == -1){
			perror("signal(mutex)");
			exit(EXIT_SUCCESS);
		}
	}
	
	exit(EXIT_SUCCESS);
}