#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    const char *path = ".";
    DIR *d;
    struct dirent *dir;
    struct stat info;
    d = opendir(path);

    if (d == NULL) {
      printf("opendir");
      return 0;
    }

    if (argc == 1) {
      while ((dir = readdir(d)) != NULL) {
        if (dir->d_name[0] != '.') {
          printf("%s\n", dir->d_name);
        }
      }
    }
    for (int i=1; i < argc; i++) {
      if ((strncmp(argv[i], "-l", 2)) == 0) {

      }
      if ((strncmp(argv[i], "-a", 2)) == 0) {
        while ((dir = readdir(d)) != NULL) {
          printf("%s\n", dir->d_name);
        }
      }
      if (argv[i] == "-la" || argv[i] == "-al") {

      }
    }
}
