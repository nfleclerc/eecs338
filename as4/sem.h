#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SEMKEY 77
#define SHMKEY 77
#define NUM_SEMS 2

#define K 1024
#define MUTEX 0
#define WLIST 1

struct sharedvar {
	int balance;
	int wcount;
	int * ary;
};

union semun {
        int val;    
        struct semid_ds *buf;           
        signed short *array;         
};

void semwait(int semid, int semaphore){
    struct sembuf psembuf;

    psembuf.sem_op = -1;
    psembuf.sem_flg = 0;
    psembuf.sem_num = semaphore;
    semop(semid, &psembuf, 1);
    return;
}

void semsignal(int semid, int semaphore){
    struct sembuf vsembuf;

    vsembuf.sem_op = 1;
    vsembuf.sem_flg = 0;
    vsembuf.sem_num = semaphore;
    semop(semid, &vsembuf, 1);
    return;
}


