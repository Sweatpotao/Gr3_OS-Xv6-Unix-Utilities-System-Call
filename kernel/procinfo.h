#ifndef __PROCINFO_H
#define __PROCINFO_H

struct procinfo {
  int pid;           // pid của tiến trình
  int ppid;          // pid của tiến trình cha
  int state;         // trạng thái
  uint64 sz;         // kích thước bộ nhớ
  char name[16];     // name
};

#endif