#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/procinfo.h"

char*
statename(int state)
{
  switch(state){
    case 1: return "SLEEPING";
    case 2: return "RUNNABLE";
    case 3: return "RUNNING";
    case 4: return "ZOMBIE";
    default: return "UNKNOWN";
  }
}

int
main(int argc, char *argv[])
{
  struct procinfo info;

  if(argc < 2){
    fprintf(2, "usage: procinfo <pid>\n");
    exit(1);
  }

  int pid = atoi(argv[1]);

  if(procinfo(pid, &info) < 0){
    fprintf(2, "procinfo: process %d not found\n", pid);
    exit(1);
  }

  printf("Process : %s\n", info.name);
  printf("PID     : %d\n", info.pid);
  printf("PPID    : %d\n", info.ppid);
  printf("State   : %s\n", statename(info.state));
  printf("Memory  : %lu bytes\n", info.sz);

  exit(0);
}