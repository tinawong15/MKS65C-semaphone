#include "ctrl.h"

#define KEY 0xCAFEEEEE

int main() {

  char * line = 
  int semd;
  semd = semget(KEY, 1, 0);


  //DOWNING
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(semd, &sb, 1);

  printf("got the semaphore!\n");
  sleep(1);

  //UPPING
  sb.sem_op = 1;
  semop(semd, &sb, 1);

  return 0;
}
