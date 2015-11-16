#include <rpc/rpc.h>
#include "cookie.h"


int *
getmemycookie_1_svc(args *argp, struct svc_req *rqstp) {

	static int *result;

	printf("%s is requesting a cookie\n", argp->name);

	if (argp->cookiecount == 0){
		result = (int *)-2;
	} else if (strcmp(argp->name, "Judy")){
		result = (int *)-1;
	} else {
		result = (int *)1;
	}

	return &result;

}
