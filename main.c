#include "ctrl.h"

#define KEY 0xCAFEEEEE

int main() {
  int shmid;
  union semun us;
  int semd;
  char *data;
  semd = semget(KEY, 1, 0);

  //DOWNING
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(semd, &sb, 1);

  shmid = shmget(KEY, 256, 0644);
  if(shmid == -1) {
    printf("Error: %s\n", strerror(errno));
    return 1;
  }

  data = shmat(shmid, (void *)0, 0);
  int len = strlen(data);

  //UPPING
  sb.sem_op = 1;
  semop(semd, &sb, 1);

  return 0;
}
