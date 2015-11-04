/*
complie:
gcc -o ./bin/shared_memory shared_memory.c

running: shared_memory [shmkey] [semkey]
./bin/shared_memory 1234 1567
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>

struct sembuf waitsem[] = { {0,-1,0} };
struct sembuf notifysem[] = { {0,+1,0} };

char *shm_data;
int shmid, semid;


union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int  *array;
  struct semifo *__buf;
} semarg;

void errquit(char* message)
{
  perror(message);
  exit(1);
}

void fork_and_run()
{
  pid_t pid = fork();
  if(pid<0) {
    errquit("fork() fail");
  }
  else {
    busy();
    exit(0);
  }
}

int access_shm()
{
  int i;
  pid_t pid;
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 100000000;
  sprintf(shm_data, "%d", getpid());

  for(i=0; i<1000; ++i);

  pid=atoi(shm_data);
  if(pid != getpid())
    puts("error : attach other process\n");
  else
    printf("ok\n");

  fflush(stdout);
  nanosleep(&ts, NULL);
  return 0;
}

int busy()
{
  int i = 0;
  for(i=0; i<10; ++i) {
    semop(semid, &waitsem[0], 1);
    access_shm();
    semop(semid, &notifysem[0], 1);
  }
  shmdt(shm_data);
  return 0;
}

int main(int argc, char *argv[])
{
  key_t shmkey, semkey;
  unsigned short initsemval[1];
  if(argc < 2) {
    printf("Usage : %s shmkey semkey\n", argv[0]);
    exit(1);
  }

  shmkey = atoi(argv[1]);
  semkey = atoi(argv[2]);

  shmid = shmget(shmkey, 128, IPC_CREAT|0600);
  if(shmid < 0)
    errquit("shmget fail");

  shm_data = (char*)shmat(shmid, (void*)0, 0);

  if(shm_data == (char*)-1)
    errquit("shmat fail");

  semid = semget(semkey, 1, IPC_CREAT | 0600);
  if(semid == -1)
    errquit("semget fail");

  initsemval[0] = 1;
  semarg.array = initsemval;

  if(semctl(semid,0,SETALL,semarg) == -1)
    errquit("semctl fail");

  fork_and_run();
  fork_and_run();

  busy();

  wait(NULL);
  wait(NULL);

  shmctl(shmid,IPC_RMID,0);
  shmctl(semid,IPC_RMID,0);
  return 0;
}
