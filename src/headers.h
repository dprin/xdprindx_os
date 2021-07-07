#ifndef HEADERS
#define HEADERS

#include <unistd.h>
#include <dirent.h>

#include "./boot.h"
#include "./cmds/commands.h"

void run(int debug){
  while (1 == 1){
  boot(debug);
    while (2 == 2){
      getInput(debug);
      if (exitLoop == 1){
        exitLoop = 0;
        break;
      }
    }
  }
}

#endif
