#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void prime(int p[]){
  int x,y;
  int child_p[2];
  // 子进程
  // 从 p[0] 接收
  close(p[1]);
  
  if(read(p[0],&x,sizeof(int))){
    // 接收的第一个数据肯定是素数,打印出来
    fprintf(stdout,"prime:%d\n",x);
    // 处理其它数字
    pipe(child_p);
    int pid = fork();
    if(pid > 0){
      // 父进程
      close(child_p[0]);
      while(read(p[0], &y,sizeof(int))){
        if(y%x != 0){
          // 其它不能被 x 整除的数,全部发往下一个子进程
          write(child_p[1], &y, sizeof(int));
        }
      }
      close(p[0]);
      close(child_p[1]);
      // 返回
      int status;
      wait(&status);
    }else if(pid == 0){
      prime(child_p);
    }
  }
  exit(0);

}

int main(){

  int p[2];
  pipe(p);
  int pid = fork();

  if(pid == 0){
    // 递归实现
    prime(p);
    
  }else if(pid > 0){
    close(p[0]);
    // 父进程将数据传给子进程
    for(int i = 2; i <= 35; i++){
      write(p[1], &i,sizeof(int));
    }
    close(p[1]);
    int status;
    wait(&status);
  }else{
    fprintf(stdout, "err for fork()\n");
    return 1;
  }
  
  return 0;
}
