#include "ctrl.h"

#define KEY 0xCAFEEEEE

// create function
int create(){
  printf("Creating Semaphore...\n");

  // ceates shared memory
  int shmid = shmget(KEY, sizeof(int), 0644 | IPC_CREAT);
  if (shmid == -1){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }

  // creates semaphore
  int semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semid == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }

  union semun s;
  s.val = 1;
  int sem_status = semctl(semid, 0, SETVAL, s);
  if (sem_status == -1){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }

  // creates file story.txt
  int fd = open("story.txt", O_CREAT | O_TRUNC);
  if (fd == -1){
    printf("File: %s\n", strerror(errno));
    return 1;
  }

  return 0;
}

// view function
int view(){
  printf("Viewing Semaphore...\n");

  int fd = open("story.txt", O_RDONLY);
  if (fd == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }
  char * file = calloc(2056, sizeof(char));
  int read_status = read(fd, file, 2056);
  if (read_status == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }
  printf("'%s'\n", file);
  close(fd);
  return 0;
}

// remove function
int rem(){
  printf("Removing Semaphore...\n");

  int shmid = shmget(KEY, sizeof(int), 0644);
  if (shmid == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }
  int semd = semget(KEY, 1, 0644);
  if (semd == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }

  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  int semop_status = semop(semd, &sb, 1);


  int sem_status = semctl(semd, 0, IPC_RMID, NULL);
  if (sem_status == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }

  view();

  remove("story.txt");

  return 0;
}


// main
int main(int argc, char * argv[]) {
  if (argc == 1){
    printf("Usage: make setup [flag]\n   Or: ./control [flag]\n" );
    return 0;
  }

  char * flag = argv[1];

  if (strcmp("-c", flag) == 0){
    return create();
  }
  if (strcmp("-r", flag) == 0){
    return rem();
  }
  if (strcmp("-v", flag) == 0){
    return view();
  }
  else {
    printf("Flag provided is not one of the three flags: -c, -r, -v\n");
  }

  return 0;
}
