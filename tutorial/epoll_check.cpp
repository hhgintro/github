#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

int main()
{
    int epoll_fd;
    if((epoll_fd = epoll_create(500) == -1)) {
        printf("epoll file descriptor create fail\n");
        return 0;
    }

    printf("epoll file descriptor create success\n");
    close(epoll_fd);
}
