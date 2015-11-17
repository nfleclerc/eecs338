#include <stdio.h>
#include <rpc/rpc.h>
#include "cookie.h"

int cookiecount;
int tinacount;

int *
getmemygookie_1_svc(cookieargs *argp, struct svc_req *rqstp)
{
	static int  result;

	if (cookiecount == 0){
		printf("Sorry kiddos no cookies left!");
		fflush(0);
		result = -2;
	} else if (strcmp("Judy", argp->name) && tinacount < 2){
		printf("Mom: Judy you can't have a cookie now, you need to wait for Tina to have %d more.\n", 2 - tinacount);
		fflush(0);
		result = -1;
	} else {
		cookiecount--;
		printf("Mom: There are %d cookies left.\n", cookiecount);
		fflush(0);
		result = 1;
	}

	return &result;
}
