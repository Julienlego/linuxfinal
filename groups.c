#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

void getGroupsForUser(char *name) {

	int i = 1, j, maxNumGroups = 32;
	gid_t *groups;
	struct passwd *pw;
	struct group *gr;

	groups = malloc(maxNumGroups * sizeof (gid_t));
	pw = getpwnam(name);

	if (pw == NULL) {
			printf("%s is not a user\nTry searching again \n", name);
			exit(EXIT_FAILURE);
	}

	if (getgrouplist(name, pw->pw_gid, groups, &maxNumGroups) == -1) {
			printf("Cant find groups \n");
	}

	for (j = 0; j < maxNumGroups; j++) {
		gr = getgrgid(groups[j]);
		if (gr != NULL)
			printf("%s ", gr->gr_name);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	int i = 1, j, maxNumGroups = 32;
	gid_t *groups;
	uid_t *uid;
	struct passwd *currentUser;
	char *name;

	if (argc == 1) {
		uid = geteuid();
		currentUser = getpwuid(uid);
		name = currentUser->pw_name;
		getGroupsForUser(name);
	}
	else {
		for (i = 1; i < argc; i++) {
			name = argv[i];
			getGroupsForUser(name);
		}
	}
}
