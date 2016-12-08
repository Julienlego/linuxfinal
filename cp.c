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

//Fully working. Copies a file to another/creates a new file
//Additionally copies a file to a directory path
void copyFile(char *f1, char *f2) {
  FILE *source, *target;
  DIR *dir;
  char ch;
  struct stat info1;
  char buff[PATH_MAX + 1];
  char *cwd = getcwd( buff, PATH_MAX + 1);
  source=fopen(f1,"w");

  printf("source : %s\n", f1);
  printf("dest : %s\n", f2);
  if (source==NULL) {
    perror("Cannot open file");
    exit(1);
  }

  if(S_ISREG(info1.st_mode)) {
    target=fopen(f2,"w");
    printf("CWD: %s\n", cwd);
    while((ch=fgetc(source))!=EOF)
      fputc(ch,target);
  }

  if (S_ISDIR(info1.st_mode)) {
    chdir(f2);
    printf("CWD: %s\n", cwd);
    target=fopen(f1,"w");
    while((ch=fgetc(source))!=EOF)
      fputc(ch,target);
  }

  printf("Copy successful\n");
  fclose(source);
  fclose(target);
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(strcat(result, "/"), s2);
    return result;
}

void listDir (char *source, char *destination) {
    DIR* d;
    struct dirent *direntp;
    char *dName;
    char ch;
    struct stat info;
    char path[PATH_MAX];
    char *filePath;
    char buff[PATH_MAX + 1];
    char *cwd = getcwd( buff, PATH_MAX + 1);

    d = opendir( source );
    if( d == NULL ) {
      perror("Cannot open");
      printf( "Can't open %s\n", source );
      exit(1);
    }

    while(1) {
      direntp = readdir( d );
      if (!direntp) {
        break;
      }
      dName = direntp->d_name;
      stat(dName, &info);
      // printf("dName = %s\n", dName);
      // printf("%s/%s\n", source, dName);
      filePath = concat(source, dName);
      printf("filePath: %s\n", filePath);
      if (direntp->d_type & DT_DIR) {
      // if (S_ISDIR(info.st_mode)) {
        if (strcmp (dName, "..") != 0 &&
            strcmp (dName, ".") != 0) {
            int path_length;
            path_length = snprintf (path, PATH_MAX,
                                    "%s/%s", source, dName);
            // chdir(source);
            // printf("path: %s\n", path);
            // printf("%s/%s\n", source, dName);
            // mkdir(path, S_IRWXU);
            if (path_length >= PATH_MAX) {
                fprintf (stderr, "Path length has got too long.\n");
                exit (EXIT_FAILURE);
            }
            listDir(path, source);
        }
      } else {
        copyFile(filePath, destination);
      }
    }

    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 source, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

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
