struct cookieargs {
	int *tinacount;
	char *name;
};

program COOKIE_PRG {
	version COOKIE_VER {
		int getmemycookie(cookieargs) = 1;
	} = 1;
} = 28855;
