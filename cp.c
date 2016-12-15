#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int copyFile(const char* src, const char* dest);
int copyRecursive(const char* src, const char* dest);

int main (int argc, char* argv[]) {
  int isRecursive = 0;
  char *rFlag = "-r";
  char src[256];
  char dest[256];
  if (argc > 2) {
    //looks for -r option
    if (strcmp(argv[1], rFlag) == 0) {
      isRecursive = 1;
    }
    if (argc < 5) {
      sprintf(src, "%s", argv[2]);
      sprintf(dest, "%s", argv[3]);
      int status = 0;
      if (isRecursive && argc == 4) {
        status = copyRecursive(src, dest);
        if (status == 1) {
        }
      } else if (argc == 3) {
        status = copyFile(src, dest);
        if (status == 1) {
        }
      } else {
        printf("Incorrect amount of args\n");
      }
    } else {
      printf("Too many args\n");
    }
  }
  else {
    printf("Too little args\n");
  }
    return 0;
  }

int copyFile(const char* src, const char* dest) {
  int fSource, fDest, sizer, sizew;
  char buffer[2048];
  struct stat info;

  stat(src, &info);
  // check if dir
  if (S_ISDIR(info.st_mode)) {
    printf("%s is a directory\n", src);
    return 1;
  }

  char destination[256];

  //reset destination string
  for (int i = 0; i < 256; i++) {
    destination[i] = 0;
  }

  strcat(destination, dest);

  stat(dest, &info);
  if (S_ISDIR(info.st_mode)) {
    char file[256];
    int i = strlen(src) - 1;

    while(src[i] != '/' && i > -1) {
      i--;
    }
    i++;
    int j = 0;

    while(i < strlen(src)) {
      file[j] = src[i];
      i++;
      j++;
    }
    file[j] = 0;

    //check for directory ending in a /
    if (destination[strlen(destination) - 1] == '/') {
      sprintf(destination, "%s%s", destination, file);
    } else {
      sprintf(destination, "%s/%s", destination, file);
    }
  }

  //now we make it a const :(
  const char* postdestination = destination;

  //open the files
  fSource = open(src, O_RDONLY);
  if (fSource < 0) {
    // printf("Error! Cannot open %s\n", src);
    perror("Error");
    return 1;
  }
  fDest = open(postdestination, O_WRONLY | O_CREAT, 0777);
  if (fDest < 0) {
    printf("Error! cannot open %s\n", postdestination);
    perror("Error");
    return 1;
  }

  //copy the stuff over
  sizer = read(fSource, buffer, sizeof(buffer));
  sizew = write(fDest, buffer, sizer);

  return 0;
}

int copyRecursive(const char* src, const char* dest) {

  //check if file or dir
  struct stat info;
  stat(src, &info);
  if (!S_ISDIR(info.st_mode)) {
    return copyFile(src, dest);
  }

  char destination[256];
  for (int i = 0; i < 256; i++) {
    destination[i] = 0;
  }

  sprintf(destination, "%s%s", destination, dest);
  int len = strlen(destination);
  if (destination[len - 1] != '/') {
    destination[len] = '/';
    destination[len+1] = 0;
  }

  //logic to check if dir exists
  //if not, makes a dir in specified location
  if (stat(dest, &info) == -1) {
    //create folder if it doesn't exist
    mkdir(dest, 0777);
  } else if (!S_ISDIR(info.st_mode)) {
    printf("cannot copy directory into file\n");
    return 1;
  } else {
    //Traverse to destination and create folder there
    char name[256];
    for (int i = 0; i < 256; i++) {
      name[i] = 0;
    }
    int i = strlen(src) - 1;

    if (src[i] == '/') {
      i--;
    }
    while(src[i] != '/' && i > -1) {
      i--;
    }
    i++;
    int j = 0;
    while(i < strlen(src)) {
      name[j] = src[i];
      i++;
      j++;
    }
    if (name[j - 1] != '/') {
      name[j] = '/';
      name[j+1] = 0;
    }

    //create nested dir
    strcat(destination, name);
    mkdir(destination, 0777);
  }

  struct dirent *dp;

  DIR* dirp = opendir(src);
  if (dirp == NULL) {
    printf("cp: cannot access '%s': No such file or directory\n", src);
    exit(1);
  }

  // check each file/dir in the directory
  while ((dp = readdir(dirp)) != NULL) {
    if (dp->d_name[0] != '.') {
      struct stat fileInfo;

      char path[256];
      for (int i = 0; i < 256; i++) {
        path[i] = 0;
      }

      //appends / to the filepath if not there already
      if (src[strlen(src) - 1] == '/') {
        sprintf(path, "%s%s", src, dp->d_name);
      } else {
        sprintf(path, "%s/%s", src, dp->d_name);
      }

      stat(path, &fileInfo);
      if (S_ISDIR(fileInfo.st_mode)) {
        copyRecursive(path, destination);
      } else {
        copyFile(path, destination);
      }
    }
  }
  return 0;
}
