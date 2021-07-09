#ifndef CUSTOM
#define CUSTOM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* cutstr(char* inp, int startPos, int len){
    char* ret = malloc(sizeof(char) * (len + 1));

    for (int i = startPos; i < startPos + len; i++){
        ret[i - startPos] = inp[i];
    }
    ret[len] = '\0';

    return ret;
}

char* getFile(FILE* fp){
    //finding size of file
    fseek(fp, 0, SEEK_END);
    long f_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char* ret = malloc(sizeof(char) * f_size);

    fread(ret, f_size, 1, fp);

    return ret;
}

#endif