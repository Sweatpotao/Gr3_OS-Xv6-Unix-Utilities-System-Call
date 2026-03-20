#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  char buf[512];
  char *args[MAXARG];
  int i;

  if(argc < 2){
    fprintf(2, "usage: xargs command [args...]\n");
    exit(1);
  }

  for(i = 1; i < argc; i++){
    args[i-1] = argv[i];
  }

  int base_argc = argc - 1;
  char c;
  int idx = 0;

  while(read(0, &c, 1) > 0) {
    if(c == '\n') {
      buf[idx] = 0;
      
      if(fork() == 0) {
        args[base_argc] = buf;
        args[base_argc + 1] = 0;
        exec(args[0], args);
        exit(1);
      }
      wait(0);
      idx = 0;
    } else {
      if(idx < sizeof(buf) - 1) {
        buf[idx++] = c;
      }
    }
  }
  exit(0);
}
