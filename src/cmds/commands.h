#ifndef COMMANDS
#define COMMANDS

#include "fm.h"
#include "um.h"

int inputSpaces = 0;
int exitLoop = 0;

char* getCD(){
    long i;
    for (i = strlen(directory) - 1; directory[i - 1] != '/'; i--);

    return cutstr(directory, i, strlen(directory) - i - 1);
}

char* getCommand(char* input){
    if (inputSpaces == 0) return input;

    long i;
    for (i = 0; input[i] != ' '; i++);

    return cutstr(input, 0, i);
}

char* getArg(char* input, int arg){
    int spaceC = 0, i, sog; //sog = start of argument

    for (i = 0; i != strlen(input); i++){
        if (input[i] == ' '){
            spaceC++;
            if (spaceC == arg)
                sog = i + 1;
            if (spaceC == arg + 1)
                break;
        }
    }
    if (debug == 1) printf(KGRN"[DEBUG]:"KNRM" arg: %s\n", cutstr(input, sog, i - sog));

    return cutstr(input, sog, i - sog);
}

void doCommand(char* input){
    char* command = malloc(sizeof(char) * 257);
    strcpy(command, getCommand(input));

    if (strlen(input) != 0){ //cause sometimes it is annoying :v
        if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"user entered: \"%s\" \n",input);
        if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"inputSpaces = %i \n", inputSpaces);
    }

    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM "command entered is \"%s\"\n",command);

    //each command will have a comment above it to make it easier to read

    //test
    if ((strcmp(command,"test")) == 0 && inputSpaces == 1){
        printf("arguments: %s (size: %li) \n", (getArg(input, 1)), strlen(getArg(input, 1)));
    }

    //clear
    else if ((strcmp(command, "clear")) == 0 && inputSpaces == 0){
        for (int i = 0; i != 50; i++) printf("\n");
    }

    //makedir
    else if ((strcmp(command,"makedir")) == 0 && inputSpaces == 1){
        makedir(getArg(input, 1));
    }

    //remdir
    else if ((strcmp(command, "remdir")) == 0 && inputSpaces == 1){
        remdir(getArg(input, 1));
    }

    //makefile
    else if ((strcmp(command, "makefile")) == 0 && inputSpaces == 1){
        makefile(getArg(input, 1));
    }

    //remfile
    else if ((strcmp(command, "remfile")) == 0 && inputSpaces == 1){
        remfile(getArg(input, 1));
    }

    //cd
    else if ((strcmp(command, "cd")) == 0 && inputSpaces == 1){
        cd(getArg(input, 1));
    }

    //ls
    else if ((strcmp(command, "ls")) == 0 && inputSpaces == 0){
        ls();
    }

    //makeusr
    else if ((strcmp(command, "makeusr")) == 0 && inputSpaces == 2){
        makeusr(getArg(input, 1), atoi(getArg(input, 2)));
    }

    //delusr
    else if ((strcmp(command, "delusr")) == 0 && inputSpaces == 1){
        delusr(getArg(input, 1));
    }

    //exit
    else if ((strcmp(command, "exit")) == 0 && inputSpaces == 0){
        exitLoop = 1;
    }

    else {
        printf("Sorry, \"%s\" doesn't exist\n", command);
    }

    free(command);
}

void getInput(){
    char* input = malloc(sizeof(char) * 2560);
    char* CD = getCD(directory);

    printf("%s@%s> ", username, CD);
    fgets(input,2560, stdin);

    //cleaning the input string so that it can be somewhat usable
    input[strlen(input) - 1] = '\0'; //removing '\n' at the end of the string
    while(input[strlen(input) - 1] == ' ') input[strlen(input) - 1] = '\0'; //removing additional spaces at the end of the string
    while(input[0] == ' ') memmove(input, input + 1, strlen(input)); //removing additional spaces at the start of the string

    for(int i = 0; i != strlen(input); i++){ //this for loop look into input and checks for extra spaces inside of string
        if (input[i] == ' ' && input[i + 1] == ' '){ //checks for 2 spaces next to each other
          memmove(&input[i + 1], &input[i + 2], strlen(input) - (i + 1)); //removes the spaces
          i--; //for some reason it only works if i-- is done
        }
    }

    for (int i = 0; i != strlen(input); i++) //looping through string to see how many spaces there are
        if (input[i] == ' ')
            inputSpaces++;

    doCommand(input);
    inputSpaces = 0;

    free(input);
}

#endif