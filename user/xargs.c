#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char buf[512]; // Toàn bộ line
  char *args[MAXARG]; // Con trỏ trỏ vào từng từ bên trong buf
  int i;

  // 1. Check cú pháp: phải có command
  if(argc < 2){
    fprintf(2, "usage: xargs command [args...]\n");
    exit(1);
  }

  // 2. Copy command + fixed arguments
  for(i = 1; i < argc; i++){
    args[i-1] = argv[i];
  }
  int base = argc - 1; // số argument cố định

  int idx = 0;

  // 3. Đọc stdin từng ký tự
  while(read(0, &buf[idx], 1) > 0){
    if(buf[idx] == '\n'){
      buf[idx] = 0;

      int n = base;
      char *p = buf;

      // 4. Tách dòng thành argument
      while(*p){
        while(*p == ' ')
          p++;
        if(*p == 0)
          break;

        if(n >= MAXARG - 1){
          fprintf(2, "xargs: too many arguments\n");
          break;
        }

        args[n++] = p; // Lưu vị trí của từ 
        while(*p && *p != ' ')
          p++;
        if(*p){
          *p = 0;
          p++;
        }
      }

      args[n] = 0;

      // 5. fork + exec
      if(fork() == 0){
        exec(args[0], args);
        fprintf(2, "exec failed\n");
        exit(1);
      }
      wait(0);

      idx = 0;
    } else {
      idx++;
    }
  }

  exit(0);
}
