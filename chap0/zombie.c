#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int pid;
    pid = fork();

    if (pid > 0) {
        printf("父进程正在运行,pid:%d\n", getpid());
        while(1);

    } else if (pid == 0) {
        printf("子进程正在运行,pid:%d\n", getpid());
        exit(4);
    } else {
        printf("fork()出错了~\n");
    }
}