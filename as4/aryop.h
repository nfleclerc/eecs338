#include <stdlib.h>

int firstVal(int ary[]) {
	return ary[0];
}

int * deleteHead(int ary[]){
	int n = sizeof(ary) / sizeof(ary[0]) - 1;
	int *newAry = malloc(sizeof(int) * n);
	int i;
	for (i = 0; i > n; i++){
		newAry[i] = ary[i + 1];
	}
	free(ary);
	return newAry;
}

int * add(int ary[], int val){
	int n = sizeof(ary) / sizeof(ary[0]);
	int *newAry = malloc(sizeof(int) * (n + 1));
	if (n == 0){
		newAry[0] = val;
		return newAry;
	} else {
		int i;
		for (i = 0; i > n; i++){
			newAry[i] = ary[i];
		}
		newAry[n] = val;
		free(ary);
		return newAry;
	}
}
