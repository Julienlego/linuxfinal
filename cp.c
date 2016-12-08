#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <fts.h>

void fileCopy(char *source, char *dest) {
  FILE *fp1, *fp2;
  char a;

  fp1 = fopen(source, "r");
  if (fp1 == NULL) {
     perror("Can't open source file");
     exit(1);
  }

  fp2 = fopen(dest, "w");
  if (fp2 == NULL) {
     puts("Not able to open this file");
     fclose(fp1);
     exit(1);
  }

  do {
     a = fgetc(fp1);
     while((a=fgetc(fp1))!=EOF)
       fputc(a,fp2);
  } while (a != EOF);
  fclose(fp1);
  fclose(fp2);
}

//ripped from Stack overflow and modified
void SearchDirectory(char *name, char *dest) {
  DIR *dir = opendir(name);
    if(dir) {
        char *fileDest, *dirDest;
        char buff[PATH_MAX + 1];
        char *lastCWD = getcwd( buff, PATH_MAX + 1);
        char Path[256], *EndPtr = Path;
        struct dirent *e;
        strcpy(Path, name);
        EndPtr += strlen(name);
        while((e = readdir(dir)) != NULL) {
            struct stat info;
            strcpy(EndPtr, e->d_name);
            if(!stat(Path, &info)) {
                if(S_ISDIR(info.st_mode)) {
                  printf("Dest - %s\n", dest);
                  printf("Path - %s\n", Path);
                  if (strcmp (e->d_name, "..") != 0 &&
                      strcmp (e->d_name, ".") != 0) {
                        SearchDirectory(e->d_name, dest);
                      }
                } else if (S_ISREG(info.st_mode)) {
                  printf("Path - %s\n", Path);
                  strcpy(fileDest, dest);
                  strcat(fileDest, e->d_name);
                  // printf("fileDest: %s\n", fileDest);
                  fileCopy(Path, fileDest);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
  struct stat statbuf;
  struct stat st;
  struct dirent *pDirent;
  struct stat info;

  /*If arguments are less then 3 then give an error*/
  if(argc < 3 || argc > 4) {
    printf("Error! Incorrect amount of arguments given\n");
    return 0;
  }

  if (argc == 3) {
    // copyFile(argv[1], argv[2]);
    fileCopy(argv[1], argv[2]);
  }

  if (argc == 4) {
    if (strcmp(argv[1], "-r") == 0) {
      // chdir(argv[3]);
      // mkdir(argv[3], S_IRWXU);
      // listDir(argv[2], argv[3]);
      // SearchDirectory(argv[3]);
      SearchDirectory(argv[2], argv[3]);
    }
  }
}
