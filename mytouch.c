#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <utime.h>
#include <unistd.h>
#include <stdio.h>

int main(int arg, char* argv[]){
  FILE* file = fopen(argv[1], "r");
  fclose(file);

  int err;
  struct utimbuf adjust;
    
  if (arg == 2){
    adjust.actime = time(NULL);
    adjust.modtime = time(NULL);
    err = utime(argv[1], &adjust);
    if(err == -1)
      perror("Unable to adjust\n");
  }
  else if (arg == 3) {
    adjust.actime = atoi(argv[2]);
    adjust.modtime = atoi(argv[2]);
    err = utime(argv[1], &adjust);
    if(err == -1)
     perror("2: Unable to adjust\n");
 }
  else
    exit(1);
  return 0;
}
