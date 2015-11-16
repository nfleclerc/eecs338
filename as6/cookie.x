struct args {
	int cookiecount;
	char* name;
};

program COOKIE_PRG {
	version COOKIE_VER {
		int getmemycookie( args ) = 1;
	} = 1;
} = 22855;  
