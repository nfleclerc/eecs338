#include "cookie.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void
cookie_prg_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	char * name = "Judy";

	clnt = clnt_create (host, COOKIE_PRG, COOKIE_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (EXIT_FAILURE);
	}

	time_t rawtime;
  	struct tm * timeinfo;
	char hostname[1024];
	hostname[1023] = '\0';

	do {
		sleep(1);
		result_1 = getmemycookie_1(&name, clnt);
		if (result_1 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		} else if (*result_1 == -2){
			printf("Judy: Mommy can you bake more cookies?\n");
  			time (&rawtime);
  			timeinfo = localtime (&rawtime);
  			printf ("Judy: %i %s\n", gethostname(hostname, 1023), asctime(timeinfo));
			fflush(0);
		} else if (*result_1 == -1){
			printf("Judy: It's no fair that Tina gets to have two and I have to wait!\n");
  			time (&rawtime);
  			timeinfo = localtime (&rawtime);
  			printf ("Judy: %i %s\n", gethostname(hostname, 1023), asctime(timeinfo));
			fflush(0);
		} else if (*result_1 == 1){
			printf("Judy: Thanks for the cookie Mommy!\n");
  			time (&rawtime);
  			timeinfo = localtime (&rawtime);
  			printf ("Judy: %i %s\n", gethostname(hostname, 1023), asctime(timeinfo));
			fflush(0);
		} 
	} while (*result_1 != -2);

	clnt_destroy (clnt);
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	cookie_prg_1 (host);
	exit (EXIT_SUCCESS);
}
