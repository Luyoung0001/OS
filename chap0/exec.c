#include <stdio.h>
#include <unistd.h>

int main() {
    char *argv[3];
    argv[0] = "/bin/echo"; // 第一个参数是可执行文件的路径
    argv[1] = "hello";     // 第二个参数是命令的参数
    argv[2] = NULL;        // 参数数组的最后一个元素必须是 NULL

    execv(argv[0], argv); // 执行 /bin/echo 命令并传递参数

    // 如果execv失败，才会执行下面的代码
    printf("exec error\n");
    return 1;
}
