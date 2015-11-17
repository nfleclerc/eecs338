#include "cookie.h"
#include <stdio.h>


void
cookie_prg_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	cookieargs  getmemygookie_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, COOKIE_PRG, COOKIE_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	while (result_1 != (int *) -2){
		result_1 = getmemygookie_1(&getmemygookie_1_arg, clnt);
		if (result_1 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		} else if (result_1 == (int *) -2){
			printf("Judy: Mommy can you bake more cookies?\n");
			fflush(0);
		} else if (result_1 == (int *) -1){
			printf("Judy: It's no fair that Tina gets to have two and I have to wait!\n");
			fflush(0);
		} else if (result_1 == (int *) 1){
			printf("Judy: Thanks for the cookie Mommy!\n");
			fflush(0);
		}
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
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
exit (0);
}
