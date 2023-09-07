#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int pid;
    pid = fork();

    if (pid > 0) {
        // 父进程
        printf("父进程正在运行,pid:%d ppid:%d\n", getpid(), getppid());
        int status;
        wait(&status);
        while (1) {
            sleep(1);
            printf("父进程正在运行,pid:%d ppid:%d\n", getpid(), getppid());
        }

    } else if (pid == 0) {
        int pid1 = fork();
        if (pid1 > 0) {
          // 子进程直接结束
            exit(0);
        } else if (pid1 == 0) {
            // 孙子进程
            printf("孙子进程正在运行,pid:%d ppid:%d\n", getpid(), getppid());
            while (1) {
                sleep(1);
                printf("孙子进程正在运行,pid:%d ppid:%d\n", getpid(),
                       getppid());
            }
        } else {
            printf("进程S fork()出错了~\n");
        }

    } else {
        printf("进程P fork()出错了~\n");
    }
}