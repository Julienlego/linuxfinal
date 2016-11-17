#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void longFormat (char *name, const char *path) {
	struct stat fileInfo;
	char appendedPath[512];
	sprintf(appendedPath, "%s/%s", path, name);
	stat(appendedPath, &fileInfo);

	printf( (S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
	printf( (fileInfo.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileInfo.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileInfo.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileInfo.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileInfo.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileInfo.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileInfo.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileInfo.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileInfo.st_mode & S_IXOTH) ? "x" : "-");

	printf(" %d", fileInfo.st_nlink);

	struct passwd *pwd;
	if ((pwd = getpwuid(fileInfo.st_uid)) != NULL)
    printf(" %s", pwd->pw_name);

	struct group *grp;
	if ((grp = getgrgid(fileInfo.st_gid)) != NULL)
		printf(" %s", grp->gr_name);

	printf(" %lld", fileInfo.st_size);

	struct tm ts;
	ts = *localtime(&fileInfo.st_mtime);
	char date[80];
	strftime(date, sizeof(date), "%b %d %H:%M", &ts);
	printf(" %s", date);
}


/*------------------------------*/

int main(int argc, char* argv[])
{
    const char *path = ".";
    DIR *d;
    struct dirent *dir;
    struct stat file;
    d = opendir(path);
    char buf[512];
    char *allFiles[512];
    char *hFiles[512];
    char *rFiles[512];
    int count = 0;
    int status = 0;
    int rCount = 0, hCount = 0;

    if (d == NULL) {
      printf("Invalid filename\n");
      return 0;
    }

    //store every file into array
    //separate hidden and regular files in different arrays
    while ((dir = readdir(d)) != NULL) {
      allFiles[count] = dir->d_name;
      if (allFiles[count][0] == '.') {
        hFiles[hCount] = allFiles[count];
        hCount++;
      }
      if (allFiles[count][0] != '.') {
        rFiles[rCount] = allFiles[count];
        rCount++;
      }
      count++;
    }

    switch (argc) {
      case 1:
        for (int i = 0; i < rCount; i++) {
          printf("%s\n", rFiles[i]);
        }
        break;
      case 2:
        //prints all in long format
        if ((strncmp(argv[1], "-la", 3) == 0 ) || ((strncmp(argv[1], "-al", 3)) == 0)) {
          for (int i = 0; i < count; i++) {
            longFormat(allFiles[i], path);
            printf(" %s\n", allFiles[i]);
          }
          return 1;
        }
        //prints long format for non hidden files
        if ((strncmp(argv[1], "-l", 2)) == 0) {
          for (int i = 0; i < rCount; i++) {
            longFormat(rFiles[i], path);
            printf(" %s", rFiles[i]);
            printf("\n");
          }
          return 1;
        }
        //prints all files including hidden
        if ((strncmp(argv[1], "-a", 2)) == 0) {
          for (int i = 0; i < count; i++) {
            printf("%s\n", allFiles[i]);
          }
          return 1;
        }
        //checks for simple ls {filename}
        for (int i = 0; i < count; i++) {
          if ((strncmp(argv[1], allFiles[i], 20)) == 0) {
            status = stat (argv[1], &file);
            if (S_ISREG(file.st_mode)) {
              printf("%s\n", argv[1]);
            }

            if (S_ISDIR(file.st_mode)) {
              DIR *d2;
              struct dirent *dir2;
              d2 = opendir(argv[1]);

              while ((dir2 = readdir(d2)) != NULL) {
                printf("%s\n", dir2->d_name);
              }
            }
          }
        }
        break;
      //Handles file argument
      case 3:
        for (int i = 0; i < count; i++) {
          if (((strncmp(argv[1], allFiles[i], 30)) == 0) || ((strncmp(argv[2], allFiles[i], 30)) == 0)) {
            status = stat(argv[1], &file);
            if (S_ISREG (file.st_mode)) {
              printf("%s\n", argv[1]);
            }
            if (S_ISDIR (file.st_mode)) {

            }
          }
        }
        break;
    }
}
