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
        dup(p[0]); // 子进程将管道的读端口拷贝在描述符0上
                   // 关闭 p 中的描述符
        close(p[0]);
        close(p[1]);
        execv(argv[0], argv); // 使用完整路径和命令名称
    } else if (pid > 0) {
        write(p[1], "hello world\n", 12);
        // 关闭 p 中的描述符
        close(p[0]);
        close(p[1]);
    } else {
        perror("fork()");
        return 1;
    }
    return 0;
}
