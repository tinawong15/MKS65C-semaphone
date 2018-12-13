# include "ctrl.h"

int main(int argc, char const *argv[]) {
  char * flag;
  if (argc > 1){
    flag = argv[1];
  }
  else {
    printf("Usage: make setup [flag]\nOr: ./control [flag]", );
    return 0;
  }

  if (strcmp("-c", flag)){

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
