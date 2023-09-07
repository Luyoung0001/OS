#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int p[2];
    char *argv[2];
    argv[0] = "/usr/bin/wc";
    argv[1] = NULL;
    pipe(p);
    int pid = fork();
    if (pid == 0) {
        close(0);
        dup(p[0]); // 重定向到标准输入
        close(p[1]); // 关闭这个输入
        execv(argv[0], argv);
    } else if (pid > 0) {
        write(p[1], "hello world\n", 12);
    } else {
        perror("fork()");
        return 1;
    }
    return 0;
}
