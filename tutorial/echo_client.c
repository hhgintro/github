#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 1024	//message buffer size
void error_handling(char *message);

/*main func*/
int main(int argc, char *argv[])
{
  int sock;	//socket descritor
  char message[BUFSIZE] = "";
  int str_len;	//read data size
  struct sockaddr_in serv_addr;	//server address info

  if(argc != 3) {
    printf("Usage : %s <IP> <port>\n", argv[0]);
    exit(1);	//process stop
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock == -1)
    error_handling("create socket error");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    error_handling("connect() error!");

  while(1) {
    /*message input / sending*/
    fputs("input message(q to Quit): ", stdout);
    fgets(message, BUFSIZE, stdin);

    if(strcmp(message, "q\n") == 0) break;
    printf("send message: (%d)%s\n", (int)strlen(message), message);
    write(sock, message, strlen(message));

    /* message read */
    str_len = read(sock, message, BUFSIZE-1);
    message[str_len] = 0;
    printf("read message: (%d)%s\n", str_len, message);
  }
  close(sock);
  return 0;
}

void error_handling(char *message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
