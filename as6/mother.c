#include <rpc/rpc.h>
#include "cookie.h"


int *
getmemycookie_1_svc(args *argp, struct svc_req *rqstp) {

	static int *result;

	printf("%s is requesting a cookie\n", argp->name);

	if (shared->cookiecount == (int *)0){
		result = -2;
	} else if (strcmp(argp->name, "Judy") && shared->tinacount > 2){
		result = -1;
	} else {
		result = 1;
	}

	return &result;

}
