#include <stdio.h>
#include <rpc/rpc.h>
#include <unistd.h>
#include "cookie.h"

int cookiecount = 20;
int tinacount = 0;

int *
getmemycookie_1_svc(char **argp, struct svc_req *rqstp)
{
	static int result;
	const char * name = *argp;
	
	sleep(1);

	if (cookiecount == 0){
		printf("Mom: Sorry kiddos no cookies left!\n");
		fflush(0);
		result = -2;
	} else if (strcmp("Judy", name) == 0 && tinacount < 2){
		printf("Mom: Judy you can't have a cookie now, you need to wait for Tina to have %d more.\n", 2 - tinacount);
		fflush(0);
		result = -1;
	}  else {
		cookiecount--;
		if (strcmp("Tina", name) == 0){
			tinacount++;
		} else if (strcmp("Judy", name) == 0){
			tinacount = 0;
		}
		printf("Mom: There are %d cookies left.\n", cookiecount);
		fflush(0);
		result = 1;
	}

	return &result;
}
