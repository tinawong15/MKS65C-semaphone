#include "ctrl.h"

#define KEY 0xCAFEEEEE

int main() {
  int semd;
  semd = semget(KEY, 1, 0);

  //DOWNING
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(semd, &sb, 1);

  int * data;
  int shmid;

  shmid = shmget(KEY, sizeof(int), 0644);
  if (shmid == -1){
    printf("%s\n", strerror(errno));
    return 0;
  }
  data = shmat(shmid, (void *) 0, 0);
  if (data == (char *)(-1)){
    perror("shmat");
  }

  int fd = open("story.txt", O_RDONLY);
  if (fd == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }
  lseek(fd, *data, SEEK_END);
  char * file = calloc(200, sizeof(char));
  int read_status = read(fd, file, 200);
  if (read_status == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }

  printf("Last Line of the Story: '%s'\n", file);
  close(fd);
  free(file);

  printf("Enter the Next Line: ");

  char * line = calloc(sizeof(char), 200);
  fgets(line, 200, stdin);
  printf("MEOW");
  fd = open("story.txt", O_APPEND | O_WRONLY);
  printf("MEw");
  if (fd == -1) {
    printf("Error: %s\n", strerror(errno));
    return 0;
  }
  int write_status = write(fd, line, 200);
  printf("MEOWasdadas");
  if (write_status == -1){
    printf("Error: %s\n", strerror(errno));
    return 0;
  }

  // updates shared memory
  *data = strlen(line);
  printf("%d", *data);

  //UPPING
  sb.sem_op = 1;
  semop(semd, &sb, 1);

  return 0;
}
