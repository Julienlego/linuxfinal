#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void SearchDirectory(const char *name) {
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
                    //Make corresponding directory in the target folder here.
                    SearchDirectory(Path);   //Calls this function AGAIN, this time with the sub-name.
                } else if(S_ISREG(info.st_mode) { //Or did we find a regular file?
                    copyFile()
                }
            }
        }
    }
}

void copyFile(char *f1, char *f2) {
  FILE *source, *target;
  char ch;

  source=fopen(f1,"r");
  target=fopen(f2,"w");

  if (source==NULL || target==NULL) {
    printf("Unable to open. ERROR opening file!!n");
    exit(1);
  }

  while((ch=fgetc(source))!=EOF)
    fputc(ch,target);

  printf("Copy is Successful\n");
  fclose(source);
  fclose(target);
}

int main(int argc, char *argv[])
{
  DIR *dir1, *dir2;
  struct stat statbuf;
  struct dirent *pDirent;
  struct stat info;

  /*If arguments are less then 3 then give an error*/
  if(argc < 3 || argc > 4) {
    printf("Error! Incorrect amount of arguments given");
    return 0;
  }

  if (argc == 3) {
    if ()
    copyFile(argv[1], argv[2]);
  }

  if (argc == 4) {
    if (strcmp(argv[1], "-r") == 0) {
      SearchDirectory(argv[2]);
    }
  }

}
