#include "kernel/types.h"
#include "user/user.h"

void prime(int p1[]) {
    close(p1[1]);
    int n;
    if (!read(p1[0], &n, 4)) {
        close(p1[0]);
        exit(0);
    }
    printf("prime %d\n", n);
    int p2[2];
    pipe(p2);
    int pid = fork();
    if (!pid) {
        prime(p2);
        exit(0);
    }
    int m;
    while (read(p1[0], &m, 4)) {
        if (m%n) {
            write(p2[1], &m, 4);
        }
    }
    close(p1[0]);
    close(p2[0]);
    close(p2[1]);
    wait(0);
    exit(0);
}

int main()
{
    int p[2];
    pipe(p);
    for (int i = 2; i <= 35; i++) {
        write(p[1], &i, 4);
    }
    prime(p);
    exit(0);
}