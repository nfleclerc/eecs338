#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

#define NUM_FORKS 4


int status;

void fetch_IDs()
{

	//char * str;
	//str = (char *) cuserid(NULL);
    	printf("User ID: %i\n", cuserid());
	printf("PID %i: User ID: %d, Effec UID: %d, Group ID: %d, Effec GID: %d\n", getpid(), getuid(), geteuid(), getgid(), getgid());
    	exit(EXIT_SUCCESS);
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
}

void process_1_stuff()
{
	sleep(1);
	printf("\nPID %i: (n (n-2)) binomial coefficient computations of integers n=2, 3, 10, start now!\n", getpid());
	fetch_IDs();
	kill(getpid());
	exit(EXIT_SUCCESS);
}

void process_2_stuff()
{
	sleep(2);
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

	sleep(12);
	
	char * args[3];
	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execvp(args[0], args);
	perror("exec() failed\n");
	fetch_IDs();
	kill(getpid());
	exit(EXIT_SUCCESS);
	
}

void parent_stuff()
{
}


int main()
{
    	pid_t pid;

    	int fork_count;

    	for(fork_count = 1; fork_count <= NUM_FORKS; fork_count++) {
       
		pid = fork();

        	if (pid > 0) {
            	parent_stuff();
        	} else if (pid == 0) {
            	switch (fork_count){
			case 1:
				process_1_stuff();
				break;
			case 2:
				process_2_stuff();
				break;
			case 3:
				process_3_stuff();
				break;
			case 4:
				process_4_stuff();
				break;
			}
        	} else {
            		perror("fork() failed\n");
            		exit(EXIT_FAILURE);
        	}
    	}
	
	return(EXIT_SUCCESS);
	
}

