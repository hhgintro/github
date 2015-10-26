#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <sys/socket.h>
#include <netdb.h>

int main()
{
    struct servent *servent;
    servent =  getservbyname("echo", "udp");

    if(servent == NULL) {
        printf("not found serice info\n");
        exit(0);
    }

    printf("UDP echo port number(network order) : %d\n", servent->s_port);
    printf("UDP echo port number(host order) : %d\n", ntohs(servent->s_port));
    return 0;
}
