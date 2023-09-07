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
        dup(p[0]);
        close(p[1]);
        execv(argv[0], argv);
    } else if (pid > 0) {
        close(0);
        close(p[0]); 
        char buffer[1024] = " sdsacas scascas \n";
        int bytesRead = 20;
        write(p[1], buffer, bytesRead);
        close(p[1]); // 关闭管道的写入端

    } else {
        perror("fork()");
        return 1;
    }
    return 0;
}
