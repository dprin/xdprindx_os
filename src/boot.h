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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int nrp = 0; //no root password
int isAdmin;

void checkFiles(int debug){
    FILE* file;
    DIR* dir = opendir("root");
    struct stat sb;
    int result;

    if ((file = fopen("usrs", "r"))){ //checking if "usrs" file exists
      if (debug == 1) printf(KGRN"[DEBUG]:"KNRM" usrs exists\n");
      fclose(file);
    }
    else nrp = 1; //if not thenno root password = 1

    if (stat("root", &sb) == 0 && S_ISDIR(sb.st_mode)){
        if (debug == 1) printf(KGRN"[DEBUG]"KNRM" root exists\n");
    }
    else{
      if((result = mkdir("root", 0777)) == -1){
        printf(KRED"Error: couldn't make directory\n\n"KNRM);
        exit(1);
      }
    }
}

void inrp(int nrp, int debug){ //inrp = if no root password
  if (nrp == 1){ //skips all of this function if nrp == 0
    FILE *fp;
    char* rpass = malloc(sizeof(char) * 261); //root password
    char* tmp = malloc(sizeof(char) * 261); //temporary string

    printf(KRED"The \"usrs\" file does not exist! (no user has been implemented into the system.)\n\n"KNRM);
    printf("Please enter root password that you want: "); scanf("%s", rpass);
    if (debug == 1) printf(KGRN"[DEBUG]:"KNRM" pass is \"%s\"\n", rpass);

    strcpy(tmp, "root ");//make tmp = "root "
    strcat(tmp, rpass);//add everything in rpass to tmp
    strcat(tmp, " 1"); //add admin permissions to root

    if (debug == 1) printf(KGRN"[DEBUG]:"KNRM" will print in file \"%s\"\n", tmp);

    fp = fopen("usrs", "a");
    fprintf(fp, "%s\n", tmp);
    fclose(fp);

    free(tmp);
    free(rpass);
  }
}

//Compares the login information the user gave with "usrs" file
int cLogin(char* username, char* password, FILE* fp, int debug){
  if (fp == NULL) return 0; //exit if nothing in file

  char* buff; //buffer
  char* tmp; //temporary
  char* un; //username
  char* ps; //password
  int c, i = 0, i1 = 0, i2 = 0; //c = character, i = increment
  size_t n = 0;

  tmp = malloc(sizeof(char) * 516);
  un = malloc(sizeof(char) * 257); //it is 257 to add the '/0' at the end
  ps = malloc(sizeof(char) * 257);

  //this finds how big the "usrs" file is
  fseek(fp, 0, SEEK_END);
  long f_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  buff = malloc(sizeof(char) * (f_size + 1));

  while ((c = fgetc(fp)) != EOF){ //add everything into the buffer string
    buff[n++] = (char) c;
  }
  buff[n] = '\0'; //end string

  n = 0; //i will user n again later

  while(n != strlen(buff)){
    while (buff[n] != '\n'){ //copy every line till it is
      c = (int) buff[n++]; //convert char into int and store it in a variable
      tmp[i++] = (char) c; //convert that int into char and store it in char* tmp
    }
    tmp[i] = '\0'; //end string
    n++; //increment n so that it doesn't loop forever

    while (tmp[i1] != ' '){ //find the username in "usrs" file
      c = (int) tmp[i1];
      un[i1++] = (char) c;
    }
    un[i1++] = '\0'; //end string

    //if the username in file and the username inputed is equal then
    //see if password isequal
    if ((strcmp(un,username)) == 0){
      while (tmp[i1] != ' '){
        c = (int) tmp[i1++];
        ps[i2++] = (char) c;
      }
      ps[i2] = '\0';

      if ((strcmp(ps, password)) == 0){
        free(buff);
        free(tmp);
        free(un);
        free(ps);
        if (tmp[i1 + 1] == '1'){
          if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"ADMIN \n");
          isAdmin = 1;
        }
        else if (tmp[i1 + 1] == '0'){
          if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"NOT ADMIN \n");
          isAdmin = 0;
        }

        return 1;
      }
      else{
        free(buff);
        free(tmp);
        free(un);
        free(ps);

        return 0;
      }
    }

    //make the "increment"ers 0
    i1 = 0;
    i = 0;
  }
  //if nothing is equal to the username entered it will return 0
  free(buff);
  free(tmp);
  free(un);
  free(ps);

  return 0;
}


void login(int debug){ //login function
  FILE* fp;
  char* userI = malloc(sizeof(char) * 256); //username input (from user)
  char* passI = malloc(sizeof(char) * 256); //password input (from user)
  int ret = 0; //this is the variable that stores what the function cLogin returns
  //same thing with retP but from cPass function

  fp = fopen("usrs", "r");

  while (ret == 0){
      printf("Please enter your username: ");
      scanf("%s", userI); printf("\n");
      printf("Please enter your password: ");
      scanf("%s", passI); printf("\n");

      ret = cLogin(userI, passI, fp, debug);
      if (debug == 1 && ret == 0) printf(KGRN"[DEBUG]: "KNRM"Username/password doesn't exists \n");
      else if (debug == 1 && ret == 1) printf(KGRN"[DEBUG]: "KNRM"Username and password exists \n");
  }

  fclose(fp);
}

void boot(int debug){
  checkFiles(debug);
  inrp(nrp, debug);
  login(debug);
}

#endif
