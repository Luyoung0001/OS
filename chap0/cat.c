#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    char buf[512];
    int n;
    for (;;) {
        n = read(0, buf, sizeof buf);
        if (n == 0) {
            break;
        } else if (n < 0) {
            fprintf(2, "read error\n");
            exit(1);
        } else if (write(1, buf, n) != n) {
            fprintf(2, "write error\n");
            exit(1);
        }
    }
}