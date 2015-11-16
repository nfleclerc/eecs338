struct args {
	int returnvalue;
	pid_t process;
};

program COOKIE_PRG {
	version COOKIE_VER {
		int getMeMyCookie( args ) = 1;
	} = 1;
} = 22855;  
