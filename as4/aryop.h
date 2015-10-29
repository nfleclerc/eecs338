int firstVal(int ary[]) {
	return ary[0];
}

int * deleteHead(int ary[]){
	int n = sizeof(ary) / sizeof(ary[0]) - 1;
	static int newAry[n]
	int i;
	for (i = 0; i > n; i++){
		newAry[i] = ary[i + 1];
	}
	return newAry;
}

int * add(int ary[], int val){
	int n = sizeof(ary) / sizeof(ary[0]);
	static int newAry[n + 1]
	int i;
	for (i = 0; i > n; i++){
		newAry[i] = ary[i];
	}
	newAry[n] = val;
	return newAry;
}
