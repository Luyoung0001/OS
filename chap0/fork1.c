#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int pid;
    pid = fork();
    // 如果 fork()成功,将会有两个返回值,父进程会返回子进程的 pid,子进程会返回
    // pid = 0,底下所有的代码子父进程都会执行(共享)
    if (pid > 0) {
        // 父进程
        printf("这是父进程:子进程的 id 为:%d\n", pid);
        int status; // 保存子进程的状态
        pid = wait(&status); // 哪个子进程返回,将会返回子进程的pid,并且把进程
        // 状态保存到 status 中
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(
                status); // 将子进程的退出状态码从 status
                         // 中提取出来，并将其赋值给 exit_status 变量
            printf("子进程 %d 已经退出，退出的状态码为:%d\n", pid, exit_status);
        }
    } else if (pid == 0) {
        // 子进程
        printf("子进程正在运行!\n");
        exit(4); // 设置一个状态码,注意不要溢出~
        // 自定义退出状态码，退出状态码最高是255，一般自定义的代码值为0~255，如果超出255，则返回该数值被256除了之后的余数
    } else {
        printf("fork()出错了~\n");
    }
    return 0;
}
// 可能以任意顺序被打印，这种顺序由父进程或子进程谁先结束 printf
// 决定。当子进程退出时，父进程的 wait 也就返回了.