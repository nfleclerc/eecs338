#include "aryop.h"
#include "sem.h"
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_FORKS 15


int semid, shmid;
short seminit[NUM_SEMS];
struct sharedvar *shared;
union semun semctlarg;

void withdraw(int withdrawal){
	printf("%d: Attempting to withdraw $%d.\n", getpid(), withdrawal);
	semwait(semid, MUTEX);
	if (shared->wcount == 0 && shared->balance > withdrawal){
		shared->balance = shared->balance - withdrawal;
		printf("%d: Withdrawal successful. Current balance after withdrawal: $%d.\n", getpid(), shared->balance);
		semsignal(semid, MUTEX);
	} else {
		shared->wcount = shared->wcount + 1;
		printf("%d: Not enough funds, please deposit more. Waiting...\n", getpid());
		shared->ary = add(shared->ary, withdrawal);
		semsignal(semid, MUTEX);
		semwait(semid, WLIST);
		shared->balance = shared->balance - firstVal(shared->ary);
		shared->ary = deleteHead(shared->ary);
		printf("%d: Enough funds now deposited. Withdrawal successful. Current balance after withdrawal: $%d.\n", getpid(), shared->balance);
		shared->wcount = shared->wcount - 1;
		if (shared->wcount > 1 && firstVal(shared->ary) < shared->balance){
			semsignal(semid, WLIST);
		} else {
			semsignal(semid, MUTEX);
		}
	}
	exit(EXIT_SUCCESS);
}

void deposit(int deposit){
	printf("%d: Attempting to deposit $%d.\n",getpid(), deposit);
	semwait(semid, MUTEX);
	shared->balance = shared->balance + deposit;
	printf("%d: Deposit Successful. Current balance after deposit: $%d.\n", getpid(), shared->balance);
	if (shared->wcount == 0){
		semsignal(semid, MUTEX);
	} else if (firstVal(shared->ary) > shared->balance){
		semsignal(semid, MUTEX);
	} else {
		semsignal(semid, WLIST);
	}
	exit(EXIT_SUCCESS);
}

void spawn_process(int type){

	switch(type){
		case 0:
			withdraw(rand() % 1000 + 1);
			break;
		case 1:
			deposit(rand() % 1000 + 1);
			break;
	}

	exit(EXIT_SUCCESS);
}


int main() {

	pid_t pid;
	
    	semid = semget(SEMKEY ,NUM_SEMS , 0777 | IPC_CREAT);
    	seminit[MUTEX] = 1;
    	seminit[WLIST] = 0;
    	semctlarg.array = seminit;
    	semctl(semid, NUM_SEMS, SETALL, semctlarg);

    	shmid = shmget(SHMKEY, 1*K, 0777 | IPC_CREAT);
    	shared = (struct sharedvar *) shmat (shmid, 0, 0); 
    	shared->balance = 500;
    	shared->wcount = 0;
	shared->ary = malloc(0);

	srand(time(NULL));

	int fork_count;
	for (fork_count = 0; fork_count < NUM_FORKS; fork_count++){

		pid = fork();
		int a;
		a = rand();

		sleep(2);

		if (pid > 0){
			
			//big daddy

		} else if (pid == 0){

			spawn_process(a % 2);


		} else {

			perror("Child failed to fork correctly");
			exit(EXIT_FAILURE);

		}
	}
	semctl(semid,NUM_SEMS,IPC_RMID,0);
    	shmctl(shmid,IPC_RMID,0);
	exit(EXIT_SUCCESS);

}
