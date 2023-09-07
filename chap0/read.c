#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *argv[3];
    argv[0] = "/bin/cat";
    argv[1] = NULL;
    close(0);
    int fd = open("input.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    int pid = fork();

    if (pid == 0) {
        printf("子进程运行!\n");
        execv(argv[0], argv);
        perror("exec");
        exit(1);
    } else if (pid > 0) {
        printf("父进程运行!\n");
        execv(argv[0], argv);
        perror("exec");
        exit(1);
    } else {
        perror("fork()");
        return 1;
    }
}
