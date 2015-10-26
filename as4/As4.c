#include "As4.h"
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define NUM_FORKS 15

void withdraw(){
	return;
}

void deposit(){
	return;
}

void spawn_process(int type){
	
	switch(type){
		case 0:
			withdraw();
			sleep(rand() % 15);
			break;
		case 1:
			deposit();
			sleep(rand() % 15);
			break;
	}

	return;
}


int main() {

	pid_t pid;

	int fork_count;
	for (fork_count = 0; fork_count < NUM_FORKS; fork_count++){

		pid = fork();

		if (pid > 0){
			
			//big daddy

		} else if (pid == 0){

			spawn_process(floor(rand() % 2));

		} else {

			perror("Child failed to fork correctly");
			exit(EXIT_FAILURE);

		}
	}

	exit(EXIT_SUCCESS);

}
