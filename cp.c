#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void copyFile(char *f1, char *f2) {
  FILE *source, *target;
  char ch;

  source=fopen(f1,"r");

  if (source==NULL) {
    printf("Unable to open. ERROR opening file!\n");
    exit(1);
  }

  target=fopen(f2,"w");

  while((ch=fgetc(source))!=EOF)
    fputc(ch,target);

  printf("Copy is Successful\n");
  fclose(source);
  fclose(target);
}

void SearchDirectory(char *file, const char *name) {
    DIR *dir = opendir(name);
    if(dir) {
        char Path[256], *EndPtr = Path;
        struct dirent *e;
        strcpy(Path, name);                  //Copies the current path to the 'Path' variable.
        EndPtr += strlen(name);              //Moves the EndPtr to the ending position.
        while((e = readdir(dir)) != NULL) {  //Iterates through the entire directory.
            struct stat info;                //Helps us know about stuff
            strcpy(EndPtr, e->d_name);       //Copies the current filename to the end of the path, overwriting it with each loop.
            if(!stat(Path, &info)) {         //stat returns zero on success.
                if(S_ISDIR(info.st_mode)) {  //Are we dealing with a directory?
                    printf("In ISDIR\n");
                    SearchDirectory(Path, file);   //Calls this function AGAIN, this time with the sub-name.
                } else if(S_ISREG(info.st_mode)) { //Or did we find a regular file?
                    printf("Copying from IS_REG\n");
                    copyFile(file, Path);
                }
            }
        }
    }
}

void copyDir () {
  DIR* dirp;
  struct dirent* direntp;

  dirp = opendir( "/Users/mac" );
  if( dirp == NULL ) {
      perror( "can't open /home/fred" );
  } else {
      for(;;) {
          direntp = readdir( dirp );
          if( direntp == NULL ) break;

          printf( "%s\n", direntp->d_name );
      }

      closedir( dirp );
  }
}

int main(int argc, char *argv[])
{
  DIR *dir1, *dir2;
  struct stat statbuf;
  struct stat st;
  struct dirent *pDirent;
  struct stat info;

  copyDir();

  /*If arguments are less then 3 then give an error*/
  if(argc < 3 || argc > 4) {
    printf("Error! Incorrect amount of arguments given");
    return 0;
  }

  if (argc == 3) {
    copyFile(argv[1], argv[2]);
  }

  if (argc == 4) {
    if (strcmp(argv[1], "-r") == 0) {
      SearchDirectory(argv[2], argv[3]);
    }
  }

}
