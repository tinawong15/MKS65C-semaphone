#include "ctrl.h"

#define KEY 0xCAFEEEEE

int create(){
  int shmid = shmget(KEY, 200, 0644 | IPC_CREAT);
  if (shmid == -1){
    printf("Error: %s\n", strerror(errno));
  }

  int semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semid == -1){
    printf("Error: %s\n", strerror(errno));
  }

  union semun s;
  s.val = 1;

  int sem_status = semctl(semid, 0, SETVAL, s);
  if (sem_status == -1){
    printf("Error: %s\n", strerror(errno));
  }
}

int main(int argc, char const *argv[]) {
  if (argc == 1){
    printf("Usage: make setup [flag]\nOr: ./control [flag]", );
    return 1;
  }

  char * flag;
  flag = argv[1];

  if (strcmp("-c", flag)){
    create();
  }
  if (strcmp("-r", flag)){

  }
  if (strcmp("-v", flag)){

  }
  else {
    printf("Flag provided is not one of the three flags: -c, -r, -v\n");
  }
  int semd;
  return 0;
}
