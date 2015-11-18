#include "cookie.h"
#include <stdio.h>
#include <stdlib.h>

void
cookie_prg_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	cookieargs  getmemycookie_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, COOKIE_PRG, COOKIE_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit(EXIT_FAILURE);
	}
#endif	/* DEBUG */

	while (result_1 != (int *) -2){
		result_1 = getmemycookie_1(&getmemycookie_1_arg, clnt);
		if (result_1 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		} else if(result_1 == (int *) -2){
			printf("Tina: Mommy why are there no cookies left?\n");
			fflush(0);
		} else if(result_1 == (int *) 1){
			printf("Tina: Thanks for the cookie Mommy!\n");
			getmemycookie_1_arg->tinacount = getmemycookie_1_arg->tinacount + 1;
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

	exit (EXIT_SUCCESS);
}


