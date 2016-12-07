/* Chris Bendel, Julien Gilbert */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
	char *cwd;
	char buff[PATH_MAX + 1];

	if (argc == 1) {
		printf("changing directory to HOME...\n");
		chdir(getenv("HOME"));
	}
	else {
		printf("changing directory to path...\n");
		chdir(argv[1]);
	}

	cwd = getcwd( buff, PATH_MAX + 1);
	if( cwd != NULL ) {
        printf( "My working directory is %s.\n", cwd );
    }

	return 0;
}
