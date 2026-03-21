#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

// Hàm bổ trợ để lấy tên cuối cùng từ đường dẫn (ví dụ: a/b/c -> c)
char* get_name(char *path) {
  char *p;
  for(p = path + strlen(path); p >= path && *p != '/'; p--);
  p++;
  return p;
}

void tree(char *path, int depth) {
  int fd;
  struct stat st;
  struct dirent de;
  char buf[512];

  if((fd = open(path, 0)) < 0) {
    fprintf(2, "tree: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0) {
    fprintf(2, "tree: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // In thụt lề (2 dấu cách mỗi cấp)
  for(int i = 0; i < depth; i++) {
    printf("  ");
  }

  // In tên (Thư mục kèm '/', File in bình thường)
  char *name = get_name(path);
  if(st.type == T_DIR) {
    printf("%s/\n", name);
  } else {
    printf("%s\n", name);
  }

  // Nếu là thư mục, duyệt các mục con
  if(st.type == T_DIR) {
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
      if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;

      // Tạo đường dẫn mới: buf = path + "/" + de.name
      strcpy(buf, path);
      int len = strlen(buf);
      if(buf[len-1] != '/') {
        buf[len++] = '/';
      }
      strcpy(buf + len, de.name);

      // Gọi đệ quy cho mục con
      tree(buf, depth + 1);
    }
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  char *path;
  if(argc < 2) path = ".";
  else path = argv[1];

  tree(path, 0);
  exit(0);
}
