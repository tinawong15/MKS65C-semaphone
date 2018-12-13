#include "ctrl.h"

#define KEY 0xCAFEEEEE

// create function
int create(){
  printf("Creating Semaphore...\n");
  
  int shmid = shmget(KEY, 200, 0644 | IPC_CREAT);
  if (shmid == -1){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }

  int semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semid == -1){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }

  union semun s;
  s.val = 1;
  int sem_status = semctl(semid, 0, SETVAL, s);
  if (sem_status == -1){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }

  int fd = open("story.txt", O_CREAT | O_TRUNC);
  if (fd == -1){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }

  return 0;
}

// remove function
int rem(){
  printf("Removing Semaphore...\n");

  int shmid = shmget(KEY, 200, 0644);
  if (shmid == -1){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }
  int semid = semget(KEY, 1, 0644);
  if (semid == -1){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }

  union semun s;
  s.val = 0;
  int sem_status = semctl(semid, 0, IPC_RMID, s);
  if (sem_status == -1){
    printf("Error: %s\n", strerror(errno));
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
    return 1;
  }
  char * file = calloc(2056, sizeof(char));
  int read_status = read(fd, file, 2056);
  // if (read_status == -1){
  //   printf("Errsasdor: %s\n", strerror(errno));
  //   return 1;
  // }
  printf("'%s'\n", file);
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
