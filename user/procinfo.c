#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int main(int argc, char *argv[]) {
  int pid;
  struct procinfo info;

  if(argc < 2) {
    fprintf(2, "Usage: procinfo <pid>\n");
    exit(1);
  }

  pid = atoi(argv[1]);

  if(procinfo(pid, &info) < 0) {
    fprintf(2, "procinfo failed\n");
    exit(1);
  }

  // In thông tin process
  printf("PID: %d\n", info.pid);
  printf("Parent PID: %d\n", info.ppid);
  printf("State: %d\n", info.state);
  printf("Size: %lu bytes\n", info.sz);
  printf("Name: %s\n", info.name);

  exit(0);
}