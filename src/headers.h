#ifndef HEADERS
#define HEADERS

#include <unistd.h>
#include <dirent.h>
int debug;

#include "./boot.h"
#include "./cmds/commands.h"

void run(){
    while (1 == 1){
    boot();
        while (2 == 2){
            getInput();
            if (exitLoop == 1){
                exitLoop = 0;
                break;
            }
        }
    }
} 

#endif
