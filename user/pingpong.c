#include "kernel/types.h"
#include "user/user.h"
int main()
{
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (!pid) {
        close(fd[1]);
        int child_pid;
        read(fd[0], &child_pid, sizeof(child_pid));
        printf("%d: received ping\n", child_pid);
        exit(0);
    }
    close(fd[0]);
    write(fd[1], &pid, sizeof(pid));
    wait(0);
    printf("%d: received pong\n", getpid());
    exit(0);
}