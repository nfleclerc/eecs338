#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"

void judy(void *shared_data){
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;
	
	while (shared->cookiecount != 0){
		
		if (sem_wait(shared->mutex) == -1){
			perror("wait(mutex)");
			exit(EXIT_SUCCESS);
		}
		
		if (shared->tinacount < (int *)2){
			
			if (sem_wait(shared->cookie) == -1){
			perror("wait(cookie)");
			exit(EXIT_SUCCESS);
			}
			
		}
		
		// critical section start
		
		shared->cookiecount = shared->cookiecount - 1;
		shared->tinacount = 0;
		
		//critical section end
		
		if (shared->tinacount >= (int *)2){
			
			if (sem_post(shared->cookie) == -1){
			perror("signal(cookie)");
			exit(EXIT_SUCCESS);
			}
			
		}
		
		if (sem_post(shared->mutex) == -1){
			perror("signal(mutex)");
			exit(EXIT_SUCCESS);
		}
	}
	
	exit(EXIT_SUCCESS);
}