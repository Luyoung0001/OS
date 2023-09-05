#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int p[2];
    char *argv[2];
    argv[0] = "wc";
    argv[1] = NULL; // 注意修改为 NULL
    pipe(p);
    if (fork() == 0) {
        close(0);
        dup(p[0]);
        close(p[0]);
        // 如果没有关闭,程序会一直等,不会出现 eof
        // 对管道执行的read会一直等待，直到有数据了或者其他绑定在这个管道写端口的描述符都已经关闭了
        close(p[1]);
        execl("/usr/bin/wc", "wc", (char *)0); // 使用完整路径和命令名称
    } else {
        write(p[1], "hello world\n", 12);
        close(p[0]);
        close(p[1]);
    }
    return 0;
}
