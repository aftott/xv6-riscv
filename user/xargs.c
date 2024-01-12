#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    char *nargv[MAXARG];
    for (int i = 1; i < argc; i++) {
        nargv[i-1] = argv[i];
    }
    nargv[argc-1] = malloc(512);
    nargv[argc] = 0;
    while (gets(nargv[argc-1], 512)) {
        if (nargv[argc-1][strlen(nargv[argc-1])-1] == '\n') {
            nargv[argc-1][strlen(nargv[argc-1])-1] = 0;
        }
        if (fork() == 0) {
            exec(argv[1], nargv);
        } else {
            wait(0);
        }
    }
    exit(0);
}