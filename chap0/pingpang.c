#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char buf[10] = {0};
    // 将用不到的文件描述符尽可能全部关闭
    int p1[2], p2[2];
    pipe(p1); // 父进程发
    pipe(p2); // 子进程发

    int pid = fork();
    if (pid == 0) {
        const char *message = "S";
        // 子进程:在 p2 中发送,p1 中接收
        close(0);
        close(2);

        close(p1[1]);
        close(p2[0]);
        // 接收
        read(p1[0], buf, 10);
        fprintf(stdout,"%d: received ping\n", getpid());
        close(p1[0]);
        // 发送
        write(p2[1], message, 2); // 注意这里是 2
        // 发送完就关闭
        close(p2[1]);
        // exit(0);
    } else if (pid > 0) {
        const char *message = "F";
        // 父进程:在 p1 中 发送,p2 中 接收
        close(0);
        close(2);
        close(p1[0]);
        close(p2[1]);

        // 发送
        write(p1[1], message, 2); // 注意这里是 2
        // 发送完就关闭
        close(p1[1]);
      
        // 接收
        read(p2[0], buf, 10);
        close(p2[0]);
        
        wait((int*)0);// 防止抢占1
        fprintf(stdout,"%d: received pong\n", getpid());
        
    } else {
        fprintf(stdout,"err for fork()\n");
        exit(1);
    }
    exit(0);
}