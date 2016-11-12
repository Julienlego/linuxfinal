/* Chris Bendel, Julien Gilbert
 */
#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

char* groupNameFromId(gid_t gid) {
	struct group *grp;
	grp = getgrgid(gid);
	return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t groupIdFromName(const char *name) {
	struct group *grp;
	gid_t  g;
	char *endptr;

	if (name == NULL || *name == '\0')
		return -1;

	g = strtol(name, &endptr, 10);
	if (*endptr == '\0') 
		return g;
	grp = getgrnam(name);
	if (grp == NULL)
		return -1;
	return grp->gr_gid;
}

int main(int argc, char *argv[])
{
	struct passwd *p = getpwuid(getuid());
	int j, i;
	gid_t *groups;
	struct group *g;
	g = getgrgid(groups[0]);	
	printf("Group name: %s", g->gr_name);
	if (argc == 1)
	{
		g = getgrgid(p->pw_gid);
		printf("User: %s\n", p->pw_name);	
		printf("GroupID: %u GroupName: %s\n", p->pw_gid, g->gr_name);	
	}
	else {
		for (i = 1; i < argc; i++)
		{
			int grpID = groupIdFromName(argv[i]);
		
			printf("Name: %s GroupId: %d \n", argv[i], grpID);
		}
	}		
}

