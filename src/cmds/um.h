//user management commands such as makeusr and delusr
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UM
#define UM

void makeusr(char* name, int isAdminTmp, int debug){
    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"isAdmin= %i\n", isAdminTmp);

    if (isAdminTmp != 0 && isAdminTmp != 1){
        printf(KRED"[ERROR]: isAdmin can only be 1 or 0\n"KNRM);
        return;
    }

    if (isAdmin == 0 && isAdminTmp == 1){
        printf(KRED"[ERROR]: You need admin permissions to make an administrator user\n"KNRM);
        return;
    }

    char* passtmp = malloc(sizeof(char) * 256); //temporary password
    FILE* fp;

    printf("Enter %s's password: ", name);
    fgets(passtmp, 256, stdin);
    passtmp[strlen(passtmp) - 1] = '\0';

    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"name= %s\n", name);
    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"password= %s\n", passtmp);
    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"printing: %s:%s:%i\n", name, passtmp, isAdminTmp);

    fp = fopen("usrs", "a");
    fprintf(fp, "\n%s:%s:%i", name, passtmp, isAdminTmp);
    fclose(fp);

    free(passtmp);
}

void delusr(char* name, int debug){
    if (isAdmin = 0){
        printf(KRED"[ERROR]: You don't have any admin permissions to use this command\n"KNRM);
        return;
    }

    if (strcmp(name, "root") == 0){
        printf(KRED"[ERROR]: Not allowed to remove user root.\n"KNRM);
        return;
    }

    FILE* fp;
    fp = fopen("usrs", "r");
    char* file = getFile(fp);
    fclose(fp);

    if ((remove("usrs")) != 0){
        printf(KRED"[ERROR]: Could not remove users file.\n\n"KNRM);
        return;
    }

    FILE* newfp;
    newfp = fopen("usrs", "a");

    int exists = 0;
    char* line, *tmp;
    line = strtok_r(file, "\n", &tmp);

    fprintf(newfp, "%s\n", line);

    while((line = strtok_r(NULL, "\n", &tmp)) != NULL){
        if (strcmp(name, cutstr(line, 0, strlen(name))) == 0){
            exists = 1;
            continue;
        }

        fprintf(newfp, "%s\n", line);
    }

    fclose(newfp);
    free(line);
    free(file);

    if (exists == 0)
        printf(KRED"[ERROR]: \"%s\" does not exist.\n"KNRM, name);

    return;
}

#endif