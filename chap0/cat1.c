#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *argv[3];
    argv[0] = "/bin/cat";
    argv[1] = NULL;
    int pid = fork();
    

    if (pid == 0) {
        // 子进程
        close(0); // 关闭标准输入
        int fd = open("input.txt",
                      O_RDONLY); // 文件 0 此时标准输入指向了 "input.txt"
        if (fd < 0) {
            perror("open");
            exit(1);
        }
        execv(argv[0], argv); // 只会修改内存内容,但不会修改文件描述符表,cat
                              // 将会从文件 0 获取数据流
        perror("exec");
        exit(1);
    } else if (pid > 0) {
        // 父进程
        execv(argv[0], argv); // 子进程对 0 进程重定向不会影响父进程的文件描述符表,因此不会影响父进程从终端标准输入获取输入流
        perror("exec");
        exit(1);
    }

    return 0;
}
