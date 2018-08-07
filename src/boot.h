#ifndef BOOT
#define BOOT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int nrp = 0; //no root password

void checkFiles(){
    FILE* file;
    DIR* dir = opendir("root");
    struct stat sb;
    int result;

    if ((file = fopen("usrs", "r"))){ //checking if "usrs" file exists
      printf("[DEBUG]: usrs exists\n");
      fclose(file);
    }
    else nrp = 1; //if not thenno root password = 1

    if (stat("root", &sb) == 0 && S_ISDIR(sb.st_mode)){
        printf("[DEBUG] root exists\n");
    }
    else{
      if((result = mkdir("root", 0777)) == -1){
        printf("Error: couldn't make directory\n\n");
        exit(1);
      }
    }
}

void inrp(int nrp){ //inrp = if no root password
  if (nrp == 1){ //skips all of this function if nrp == 0
    FILE *fp;
    char* rpass = malloc(sizeof(char) * 261); //root password
    char* tmp = malloc(sizeof(char) * 261); //temporary string

    printf("The \"usrs\" file did not exist, which means there was no user.\n\n");
    printf("Please enter root password that you want: "); scanf("%s", rpass);
    printf("[DEBUG]: pass is \"%s\"\n", rpass);

    strcpy(tmp, "root ");//make tmp = "root "
    strcat(tmp, rpass);//add everything in rpass to tmp

    printf("[DEBUG]: will print in file \"%s\" \n", tmp);

    fp = fopen("usrs", "a");
    fprintf(fp, "%s\n", tmp);
    fclose(fp);

    free(tmp);
    free(rpass);
  }
}

void login(){ //login function
  FILE* fp;
  char* userI = malloc(sizeof(char) * 256); //username input (from user)
  char* userF = malloc(sizeof(char) * 256); //username file (from "usrs" file)
  char* passI = malloc(sizeof(char) * 256); //password input (from user)
  char* passF = malloc(sizeof(char) * 256); //password file (from "usrs" file)

  fp = fopen("usrs", "r");

  printf("Please enter your username: "); //ask for username
  scanf("%s\n", userI);

  fclose(fp);
}

void boot(){
  checkFiles();
  inrp(nrp);
  login();
}

#endif
