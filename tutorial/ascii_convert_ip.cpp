#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{
    struct sockaddr_in sa;
    inet_pton(AF_INET, argv[1], &sa.sin_addr);
    printf("inet_pton(%s) = 0x%X\n", argv[1], sa.sin_addr);

    char buf[32] = "";
    inet_ntop(AF_INET, &sa.sin_addr, buf, sizeof(buf));
    printf("inet_ntop(0x%X) = %s\n", sa.sin_addr, buf);

    return 0;
}
