#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"


void rpc_getmemycookie(char *host, int cookiecount){
	CLIENT *clnt;
	void *result;

	clnt = clnt_create(host, COOKIE_PRG, COOKIE_VER, "udp");
	if (clnt == NULL){
		clnt_pcreateerror(host);
		exit(EXIT_FAILURE);
	}

	result = getmemycookie_1(&cookiecount, clnt);
	if (result == (void *)NULL){
		clnt_perror (clnt, "call failed");
	}
	
	clnt_destroy(clnt);
}

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
