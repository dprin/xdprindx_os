#include "./headers.h"

int main(int argc, char* argv[]){
  int debug;

  //for debug mode (will make it look better later if i can)
  if (argc == 1) debug = 0;
  else if (argc == 2){
    if (atoi(argv[1]) == 1) debug = 1;

    else if (atoi(argv[1]) == 0) debug = 0;

    else {
      printf("./os (1 or 0 for debug mode) \n");
      return 0;
    }
  }
  else {
    printf("./os (1 or 0 for debug mode) \n");
    return 0;
  }

  run(debug);

  return 0x1;
}
