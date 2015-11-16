struct args {
	int *cookiecount;
	char *name;
};

program COOKIE_PRG {
	version COOKIE_VER {
		int getmemygookie(args) = 1;
	} = 1;
} = 28855;
