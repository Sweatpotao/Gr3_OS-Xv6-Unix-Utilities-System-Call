#ifndef __PROCINFO_H
#define __PROCINFO_H

struct procinfo {
  int pid;
  int ppid;
  int state;
  uint64 sz;
  char name[16];
};

#endif