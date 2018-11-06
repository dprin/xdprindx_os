#ifndef HEADERS
#define HEADERS

#include <unistd.h>
#include <dirent.h>

#include "./boot.h"
#include "./cmds/commands.h"

void run(int debug){
  boot(debug);
  while (2 == 2){
    getInput(debug);
  }
}

#endif
