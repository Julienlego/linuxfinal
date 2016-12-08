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

//Fully working. Copies a file to another/creates a new file
//Additionally copies a file to a directory path
void copyFile(char *f1, char *f2) {
  FILE *source, *target;
  DIR *dir;
  char ch;
  char buff[PATH_MAX + 1];
  struct stat info;
  char *cwd = getcwd( buff, PATH_MAX + 1);

  source=fopen(f1,"r");

  if (source==NULL) {
    printf("Unable to open. ERROR opening file!\n");
    exit(1);
  }

  stat(f2, &info);
  if(S_ISREG(info.st_mode)) {
    target=fopen(f2,"w");

    while((ch=fgetc(source))!=EOF)
      fputc(ch,target);
  }

  if (S_ISDIR(info.st_mode)) {
    chdir(f2);
    target=fopen(f1,"w");
    while((ch=fgetc(source))!=EOF)
      fputc(ch,target);
  }

  printf("Copy successful\n");
  fclose(source);
  fclose(target);
}

// void SearchDirectory(char *file, const char *name) {
//     DIR *dir = opendir(name);
//     if(dir) {
//         char Path[256], *EndPtr = Path;
//         struct dirent *e;
//         strcpy(Path, name);                  //Copies the current path to the 'Path' variable.
//         EndPtr += strlen(name);              //Moves the EndPtr to the ending position.
//         while((e = readdir(dir)) != NULL) {  //Iterates through the entire directory.
//             struct stat info;                //Helps us know about stuff
//             strcpy(EndPtr, e->d_name);       //Copies the current filename to the end of the path, overwriting it with each loop.
//             if(!stat(Path, &info)) {         //stat returns zero on success.
//                 if(S_ISDIR(info.st_mode)) {  //Are we dealing with a directory?
//                     printf("In ISDIR\n");
//                     SearchDirectory(Path, file);   //Calls this function AGAIN, this time with the sub-name.
//                 } else if(S_ISREG(info.st_mode)) { //Or did we find a regular file?
//                     printf("Copying from IS_REG\n");
//                     copyFile(file, Path);
//                 }
//             }
//         }
//     }
// }

void listDir (char *directory) {
  DIR* d;
  struct dirent* direntp;
  char *dName;
  struct stat info;

  d = opendir( directory );
  if( d == NULL ) {
      printf( "can't open %s\n", directory );
      exit(1);
  }
  for(;;) {
    direntp = readdir( d );
    if (!direntp)
      break;
    dName = direntp->d_name;
    // printf("dName = %s\n", dName);
    printf("%s/%s\n", directory, dName);
    if (direntp->d_type & DT_DIR) {
      if (strcmp (dName, "..") != 0 &&
          strcmp (dName, ".") != 0) {
          int path_length;
          char path[PATH_MAX];
          // if (S_ISREG(info.st_mode)) {
            // printf("file name: %s", dName);
          // }
          path_length = snprintf (path, PATH_MAX,
                                  "%s/%s", directory, dName);
          printf ("%s\n", path);
          if (path_length >= PATH_MAX) {
              fprintf (stderr, "Path length has got too long.\n");
              exit (EXIT_FAILURE);
          }
        listDir(path);
      }
    } else {
      // copyFile()
      printf("file name: %s\n", dName);
    }
  }

  if (closedir (d)) {
      fprintf (stderr, "Could not close '%s': %s\n",
               directory, strerror (errno));
      exit (EXIT_FAILURE);
  }
}

int main(int argc, char *argv[])
{
  DIR *dir1, *dir2;
  struct stat statbuf;
  struct stat st;
  struct dirent *pDirent;
  struct stat info;
  // listDir(argv[1]);

  /*If arguments are less then 3 then give an error*/
  if(argc < 3 || argc > 4) {
    printf("Error! Incorrect amount of arguments given\n");
    return 0;
  }

  if (argc == 3) {
    copyFile(argv[1], argv[2]);
  }

  // if (argc == 4) {
  //   if (strcmp(argv[1], "-r") == 0) {
  //     SearchDirectory(argv[2], argv[3]);
  //   }
  // }

}
