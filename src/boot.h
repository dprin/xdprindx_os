#ifndef BOOT
#define BOOT


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int nrp = 0; //no root password

void checkFiles(){
    FILE* file;
    DIR* dir = opendir("root");
    struct stat sb;
    int result;

    if ((file = fopen("usrs", "r"))){ //checking if "usrs" file exists
      printf(KGRN"[DEBUG]:"KNRM" usrs exists\n");
      fclose(file);
    }
    else nrp = 1; //if not thenno root password = 1

    if (stat("root", &sb) == 0 && S_ISDIR(sb.st_mode)){
        printf(KGRN"[DEBUG]"KNRM" root exists\n");
    }
    else{
      if((result = mkdir("root", 0777)) == -1){
        printf(KRED"Error: couldn't make directory\n\n"KNRM);
        exit(1);
      }
    }
}

void inrp(int nrp){ //inrp = if no root password
  if (nrp == 1){ //skips all of this function if nrp == 0
    FILE *fp;
    char* rpass = malloc(sizeof(char) * 261); //root password
    char* tmp = malloc(sizeof(char) * 261); //temporary string

    printf(KRED"The \"usrs\" file does not exist! (no user has been implemented into the system.)\n\n"KNRM);
    printf("Please enter root password that you want: "); scanf("%s", rpass);
    printf(KGRN"[DEBUG]:"KNRM" pass is \"%s\"\n", rpass);

    strcpy(tmp, "root "); //make tmp = "root "
    strcat(tmp, rpass); //add everything in rpass to tmp

    printf(KGRN"[DEBUG]:"KNRM" will print in file \"%s\"\n", tmp);

    fp = fopen("usrs", "a");
    fprintf(fp, "%s\n", tmp);
    fclose(fp);

    free(tmp);
    free(rpass);
  }
}

void boot(){


  checkFiles();
  inrp(nrp);
}

#endif
