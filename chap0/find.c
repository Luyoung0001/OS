#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
char* getfilename(char *path){
  char *p;
  // 从后面向前找
  for(p=path+strlen(path); p >= path && *p != '/'; p--){}
  return ++p;
}
int find(char *path,char *fileName){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return 1;
  }
  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return 1;
  }
  switch(st.type){
    case T_FILE:
      if (strcmp(getfilename(path), fileName) == 0) {
        printf("%s\n", path);
    }
    break;
    case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }
    strcpy(buf, path);
    // p指向 buf 最后一个字符'\0'
    p = buf+strlen(buf);
    *p++ = '/';
    // 循环读取目录,目录就是一个文件，包含一系列的 `dirent` 结构
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      // 空的文件
      if(de.inum == 0) {
        continue;
      }
      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) { 
        continue;
      }
      // 把文件名复制到 buf 
      memmove(p, de.name, DIRSIZ); 
      p[DIRSIZ] = 0;
      // 打不开就下一个
      if(stat(buf, &st) < 0){
        printf("find: cannot stat %s\n", buf);
        continue;
      }
      find(buf, fileName);
    }
    break;
  }
  close(fd);
  return 0;
}
int main(int argc,char *argv[]){
  if(argc != 3){
    exit(1);
  }
  // 这个思路就是找出argv[1]的所有文件,然后找到文件名和 argv[2]一样的文件,并打印出目录
  find(argv[1],argv[2]);
  exit(0);
}