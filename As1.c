#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

#define NUM_FORKS 4
#define LOOP_ITR 0x7fffffff

int status;
pid_t pid1, pid2, pid3, pid4;

void fetch_IDs()
{
	int i;
	printf("PID %i: User ID: %d, Effec UID: %d, Group ID: %d, Effec GID: %d\n", getpid(), getuid(), geteuid(), getgid(), getgid());
	fflush(stdout);
	for (i = 0; i < LOOP_ITR; i++){}
    	//exit(EXIT_SUCCESS);
}

int binomial_coefficient_of(int n)
{
   	int coefficient = 1;
	int i = 0;
    	while(i < (n - 2))
    	{
        	coefficient *= (n - i);
        	coefficient /= (i + 1);
		++i;
    	}
 
    	printf("PID %i: The binomial coefficient of %i is %i\n", getpid(), n, coefficient);
	fflush(stdout);
}

void process_1_stuff()
{
	sleep(1);
	pid1 = getpid();
	printf("\nPID %i: (n (n-2)) binomial coefficient computations of integers n=2, 3, 10, start now!\n", getpid());
	fflush(stdout);
	fetch_IDs();
	kill(getpid());
	exit(EXIT_SUCCESS);
}

void process_2_stuff()
{
	sleep(2);
	pid2 = getpid();
	int i;
	for (i = 2; i <= 10; i = i + 2)
	{
		binomial_coefficient_of(i);
		sleep(2);
	}
	fetch_IDs();
	kill(getpid());
	exit(EXIT_SUCCESS);
}

void process_3_stuff()
{
	
	sleep(3);
	pid3 = getpid();
	int i;
	for (i = 3; i <= 9; i = i + 2)
	{
		binomial_coefficient_of(i);
		sleep(2);
	}
	fetch_IDs();
	kill(getpid());
	exit(EXIT_SUCCESS);

}

void process_4_stuff()
{

	sleep(13);
	pid4 = getpid();
	char * args[3];
	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execvp(args[0], args);
	fflush(stdout);
	perror("exec() failed\n");
	fetch_IDs();
	kill(getpid());
	exit(EXIT_SUCCESS);
	
}

int main()
{
    	pid_t pid;

    	int fork_count;
	time_t pstart, pend, start1, end1, start2, end2, start3, end3, start4, end4;

    	for(fork_count = 1; fork_count <= NUM_FORKS; fork_count++) {

		pid = fork();

        	if (pid > 0) {
			//parent
			
		} else if (pid == 0) {
            		switch (fork_count){
				case 1:
					time(&start1);
					process_1_stuff();
					time(&end1);
					break;
				case 2:
					time(&start2);
					process_2_stuff();
					time(&end2);
					break;
				case 3:
					time(&start3);
					process_3_stuff();
					time(&start3);
					break;
				case 4:
					time(&start4);
					process_4_stuff();
					time(&start4);
					break;
			}
        	} else {
            		perror("fork() failed\n");
            		exit(EXIT_FAILURE);
        	}
    	}
	
	if (pid > 0){
		wait(-1, &status, WNOHANG);
		sleep(10);
		printf("Process 1 exited with status: %i\n",  WEXITSTATUS(status));
		printf("Process 2 exited with status: %i\n",  WEXITSTATUS(status));
		printf("Process 3 exited with status: %i\n",  WEXITSTATUS(status));
		printf("Process 4 exited with status: %i\n",  WEXITSTATUS(status));
	}
	
	
	sleep(4);
    	printf("User ID: %i\n", cuserid());
	printf("Process 1 End Time: %s", ctime(&end1));
	printf("Process 1 Elapsed Time: %f\n\n", difftime(start1, end1));
	printf("Process 2 End Time: %s", ctime(&end2));
	printf("Process 2 Elapsed Time: %f\n\n", difftime(start2, end2));
	printf("Process 3 End Time: %s", ctime(&end3));
	printf("Process 3 Elapsed Time: %f\n\n", difftime(start3, end3));
	printf("Process 4 End Time: %s", ctime(&end4));
	printf("Process 4 Elapsed Time: %f\n\n", difftime(start4, end4));
	printf("Parent Process End Time: %s", ctime(&pend));
	printf("Parent Process Elapsed Time: %f\n\n", difftime(pstart, pend));
	exit(EXIT_SUCCESS);
	return(EXIT_SUCCESS);
	
}

