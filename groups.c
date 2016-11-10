#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	int i = 1, j, maxNumGroups = 32;
	gid_t *groups;
	struct passwd *pw;
	struct group *gr;
	char *name;

	for (i = 1; i < argc; i++) {
		name = argv[i];
		groups = malloc(maxNumGroups * sizeof (gid_t));
		pw = getpwnam(name);

		if (pw == NULL) {
				printf("%s is not a user\nTry searching again \n", argv[i]);
				exit(EXIT_FAILURE);
		}

		if (getgrouplist(name, pw->pw_gid, groups, &maxNumGroups) == -1) {
				printf("Cant find groups \n");
		}

		printf("%s: ", name);
		for (j = 0; j < maxNumGroups; j++) {
			// printf("%d", groups[j]);
			gr = getgrgid(groups[j]);
			if (gr != NULL)
				printf(" (%s)", gr->gr_name);
		}
		printf("\n");
	}
}


// char* groupNameFromId(gid_t gid) {
// 	struct group *grp;
// 	grp = getgrgid(gid);
// 	return (grp == NULL) ? NULL : grp->gr_name;
// }
//
// gid_t groupIdFromName(const char *name) {
// 	struct group *grp;
// 	gid_t  g;
// 	char *endptr;
//
// 	if (name == NULL || *name == '\0')
// 		return -1;
//
// 	g = strtol(name, &endptr, 10);
// 	if (*endptr == '\0')
// 		return g;
// 	grp = getgrnam(name);
// 	if (grp == NULL)
// 		return -1;
// 	return grp->gr_gid;
// }
