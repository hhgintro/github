#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid;
    pid = fork();
    if(pid != 0) {
        printf("parent process's pid = %d\n", getpid());
        printf("parent process's ppid = %d\n", getppid());
        printf("parent process's pgrd = %d\n", getpgrp());
        printf("parent process's pgid = %d\n", getpgid(getpid()));
        printf("\n");
        return 0;
    }

    printf("child process's pid = %d\n", getpid());
    printf("child process's ppid = %d\n", getppid());
    printf("child process's pgrd = %d\n", getpgrp());
    printf("child process's pgid = %d\n", getpgid(getpid()));
    printf("\n");
    return 0;
}
