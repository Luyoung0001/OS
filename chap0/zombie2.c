#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 信号处理函数
void sigchld_handler(int signo) {
    int status; // 接收子进程的退出状态
    pid_t pid;

    // 等待所有子进程退出，避免成为僵尸进程
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("子进程 %d 已经退出，退出的状态码为:%d\n", pid,
                   WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("子进程 %d 被信号终止，信号编号为:%d\n", pid,
                   WTERMSIG(status));
        }
    }
}

int main() {
    // 注册信号处理函数
    signal(SIGCHLD, sigchld_handler);

    // 创建子进程
    int pid = fork();

    if (pid == 0) {
        // 子进程
        printf("子进程正在运行pid:%d!\n",getpid());
        sleep(10); // 模拟子进程工作
        exit(42); // 子进程退出
    } else if (pid < 0) {
        perror("fork");
        return 1;
    } else {
        // 父进程
        while (1) {
            // 做其他工作
            printf("父进程在运行!\n");
            sleep(1);
        }
    }
}
