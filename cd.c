/* Chris Bendel, Julien Gilbert */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>

int main(int argc, char *argv[]) {
	
	const char *path;
	uid_t uid = getuid();
	struct passwd* pwd = getpwuid(uid);
	
	if (!pwd)
    {
        printf("User with %u ID is unknown.\n", uid);
        return -1;
    }

    printf("User '%s' has home directory at '%s'\n", pwd->pw_name, pwd->pw_dir);

	if (argc == 1) {
		printf("changing directory to HOME...\n");
		//chdir(getenv("HOME"));
		if (chdir(pwd->pw_dir) != 0)
	    {
	        printf("Unable to change directory to '%s'\n", pwd->pw_dir);
	        return -1;
	    }
	}
	else {
		printf("changing directory to path...\n");
		chdir(argv[1]);
	}
	return 0;
}
