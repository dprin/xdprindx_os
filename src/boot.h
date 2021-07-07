#ifndef BOOT
#define BOOT

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT "\x1B[37m"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "custom.h"

int nrp = 0; //no root password
int isAdmin;
char* directory;
char* username;
struct stat sb;

void checkFiles(int debug){
    FILE* file;
    DIR* dir = opendir("root");
    int result;

    if ((file = fopen("usrs", "r"))){ //checking if "usrs" file exists
        if (debug == 1) printf(KGRN"[DEBUG]:"KNRM" usrs exists\n");
        fclose(file);
    }
    else nrp = 1; //if not then no root password = 1

    if (stat("root", &sb) == 0 && S_ISDIR(sb.st_mode)){
        if (debug == 1) printf(KGRN"[DEBUG]:"KNRM" root exists\n");
    }
    else{
        if((result = mkdir("root", 0777)) == -1){
            printf(KRED"[ERROR]:"KNRM" Couldn't make directory\n\n");
            exit(2);
        }
    } 
} 

void inrp(int debug){ //inrp = if no root password
    if (nrp == 1){ //skips all of this function if nrp == 0
        FILE *fp;
        char* rpass = malloc(sizeof(char) * 261); //root password

        printf(KRED"The \"usrs\" file does not exist! (no user has been implemented into the system.)\n\n"KNRM);
        printf("Please enter root password that you want: "); fgets(rpass, 261, stdin);

        rpass[strlen(rpass) - 1] = '\0'; //remove \n at the end of rpass
        if (debug == 1) printf(KGRN"[DEBUG]:"KNRM" pass is \"%s\"\n", rpass);
        if (debug == 1) printf(KGRN"[DEBUG]:"KNRM" will print in file \"root:%s:1\"\n", rpass);

        fp = fopen("usrs", "a");
        fprintf(fp, "root:%s:1", rpass);
        fclose(fp);

        nrp = 0;
        free(rpass);
    }
}

//Compares the login information the user gave with "usrs" file
int cLogin(char* usern, char* password, FILE* fp, int debug){
    if (fp == NULL) return 0; //exit if nothing in file

    char* tmp; //temporary
    char* line;
    char* file = getFile(fp);

    line = strtok_r(file, "\n", &tmp);
    do{
        if (strcmp(usern, cutstr(line, 0, strlen(usern))) != 0)
            continue;
        if (strcmp(password, cutstr(line, strlen(usern) + 1, strlen(password))) != 0)
            continue;

        strcpy(username, usern);

        isAdmin = atoi(cutstr(line, strlen(line) - 1, 1));

        free(line);
        return 1;
    } while((line = strtok_r(NULL, "\n", &tmp)) != NULL);

    free(line);
    return 0;
}


void login(int debug){ //login function
    FILE* fp;
    char* userI = malloc(sizeof(char) * 256); //username input (from user)
    char* passI = malloc(sizeof(char) * 256); //password input (from user)
    int ret = 0; //this is the variable that stores what the function cLogin returns

    fp = fopen("usrs", "r");

    while (ret == 0){
        printf("Please enter your username: ");
        fgets(userI, 256, stdin);
        printf("Please enter your password: ");
        fgets(passI, 256, stdin);

        userI[strlen(userI) - 1] = '\0'; //remove \n at end of string
        passI[strlen(passI) - 1] = '\0'; //remove \n at end of string

        ret = cLogin(userI, passI, fp, debug);
        if (debug == 1 && ret == 1) printf(KGRN"[DEBUG]: "KNRM"Username and password exists \n");
        if (ret == 0) printf(KRED"Username or password are incorrect"KNRM "\n");
    }

    free(userI);
    free(passI);
    fclose(fp);
}

void boot(int debug){
    directory = malloc(sizeof(char) * 2560);
    username = malloc(sizeof(char) * 256);
    strcpy(directory, "./root/");
  
    checkFiles(debug);
    inrp(debug);
    login(debug);
} 

#endif
