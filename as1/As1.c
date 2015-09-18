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
	printf("PID %i: User ID: %d, Effec UID: %d, Group ID: %d, Effec GID: %d\n", getpid(), getuid(), geteuid(), getgid(), getgid());
	fflush(stdout);
}
void binomial_coefficient_of(int n)
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

    	int fork_count, i;
	time_t pstart, pend, start1, end1, start2, end2, start3, end3, start4, end4;

	struct tms process_times;
    	clock_t presult, result1, result2, result3, result4;
    	double putime, utime1, utime2, utime3, utime4;
    	double pstime, stime1, stime2, stime3, stime4;

    	for(fork_count = 1; fork_count <= NUM_FORKS; fork_count++) {

		pid = fork();

        	if (pid > 0) {
			
			time(&pstart);
			time(&pend);
			presult = times(&process_times);
    			if (presult == (clock_t) -1) {
       				perror("times() failed\n");
       				exit(EXIT_FAILURE);
    			}    
    			putime = (double) process_times.tms_utime / CLOCKS_PER_SEC;
  			pstime = (double) process_times.tms_stime / CLOCKS_PER_SEC;
			
		} else if (pid == 0) {
            		switch (fork_count){
				case 1:
					time(&start1);
					process_1_stuff();
					for (i = 0; i < LOOP_ITR; i++){}
					time(&end1);
					result1 = times(&process_times);
    					if (result1 == (clock_t) -1) {
        					perror("times() failed\n");
        					exit(EXIT_FAILURE);
    					}    
    					utime1 = (double) process_times.tms_utime / CLOCKS_PER_SEC;
    					stime1 = (double) process_times.tms_stime / CLOCKS_PER_SEC;
					break;
				case 2:
					time(&start2);
					process_2_stuff();
					for (i = 0; i < LOOP_ITR; i++){}
					time(&end2);
					result2 = times(&process_times);
    					if (result2 == (clock_t) -1) {
        					perror("times() failed\n");
        					exit(EXIT_FAILURE);
    					}    
    					utime2 = (double) process_times.tms_utime / CLOCKS_PER_SEC;
    					stime2 = (double) process_times.tms_stime / CLOCKS_PER_SEC;
					break;
				case 3:
					time(&start3);
					process_3_stuff();
					for (i = 0; i < LOOP_ITR; i++){}
					time(&end3);
					result3 = times(&process_times);
    					if (result3 == (clock_t) -1) {
        					perror("times() failed\n");
        					exit(EXIT_FAILURE);
    					}    
    					utime3 = (double) process_times.tms_utime / CLOCKS_PER_SEC;
    					stime3 = (double) process_times.tms_stime / CLOCKS_PER_SEC;
					break;
				case 4:
					time(&start4);
					process_4_stuff();
					for (i = 0; i < LOOP_ITR; i++){}
					time(&end4);
					result4 = times(&process_times);
    					if (result4 == (clock_t) -1) {
        					perror("times() failed\n");
        					exit(EXIT_FAILURE);
    					}    
    					utime4 = (double) process_times.tms_utime / CLOCKS_PER_SEC;
    					stime4 = (double) process_times.tms_stime / CLOCKS_PER_SEC;
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
		for (i = 0; i < LOOP_ITR; i++){}
		printf("Process 1 exited with status: %i\n",  WEXITSTATUS(status));
		printf("Process 2 exited with status: %i\n",  WEXITSTATUS(status));
		printf("Process 3 exited with status: %i\n",  WEXITSTATUS(status));
		printf("Process 4 exited with status: %i\n",  WEXITSTATUS(status));
	}
	
	
	sleep(4);

    	printf("User ID: %d\n\n", cuserid());
	printf("Process 1 End Time: %s", ctime(&end1));
	printf("Process 1 Elapsed Time: %f\n", difftime(start1, end1));
	printf("P1 User time: %f\n", utime1);
    	printf("P1 System time: %f\n\n", stime1);

	printf("Process 2 End Time: %s", ctime(&end2));
	printf("Process 2 Elapsed Time: %f\n", difftime(start2, end2));
	printf("P2 User time: %f\n", utime2);
    	printf("P2 System time: %f\n\n", stime2);

	printf("Process 3 End Time: %s", ctime(&end3));
	printf("Process 3 Elapsed Time: %f\n", difftime(start3, end3));
	printf("P3 User time: %f\n", utime3);
    	printf("P3 System time: %f\n\n", stime3);

	printf("Process 4 End Time: %s", ctime(&end4));
	printf("Process 4 Elapsed Time: %f\n", difftime(start4, end4));
	printf("P4 User time: %f\n", utime4);
    	printf("P4 System time: %f\n\n", stime4);

	printf("Parent Process End Time: %s", ctime(&pend));
	printf("Parent Process Elapsed Time: %f\n", difftime(pstart, pend));
	printf("Parent User time: %f\n", putime);
    	printf("Parent System time: %f\n", pstime);

	exit(EXIT_SUCCESS);
	return(EXIT_SUCCESS);
	
}

