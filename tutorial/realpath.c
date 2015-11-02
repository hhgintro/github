#include <stdio.h>
#include <sys/param.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char path[MAXPATHLEN] = "";
  printf("argv: %s\n", argv[0]);
  printf("FILE macro: %s\n", __FILE__);
  realpath(argv[0], path);
  printf("path: %s\n", path);

  char* temp = strrchr(path, '/');
  int len = temp - path;  //
  printf("len: %d\n", len); //

  char folder[MAXPATHLEN] = "";
  memcpy(folder, path, len+1);
  printf("folder: %s\n", folder);

  char file[MAXPATHLEN] = "";
  memcpy(file, temp+1, strlen(temp)-1);
  printf("file: %s\n", file);

  return 0;
}
