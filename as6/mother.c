#include <stdio.h>
#include <rpc/rpc.h>
#include "cookie.h"

int cookiecount = 20;
int tinacount = 0;

int *
getmemycookie_1_svc(char **argp, struct svc_req *rqstp)
{
	static int result;
	const char * name = (const char *)argp;

	if (cookiecount == 0){
		printf("Sorry kiddos no cookies left!");
		fflush(0);
		result = -2;
	} else if (strcmp("Judy", name) && tinacount < 2){
		printf("Mom: Judy you can't have a cookie now, you need to wait for Tina to have %d more.\n", 2 - tinacount);
		fflush(0);
		result = -1;
	}  else {
		cookiecount--;
		if (strcmp("Tina", name)){
			tinacount++;
		} else if (strcmp("Judy", name)){
			tinacount = 0;
		}
		printf("Mom: There are %d cookies left.\n", cookiecount);
		fflush(0);
		result = 1;
	}

	return &result;
}
