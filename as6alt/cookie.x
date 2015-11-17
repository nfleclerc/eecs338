struct cookieargs {
	char *name;
};

program COOKIE_PRG {
	version COOKIE_VER {
		int getmemygookie(cookieargs) = 1;
	} = 1;
} = 28855;
