//fm stands for file management, this can include deleting, making or inserting things into files
//also it can change the user's current directory

#ifndef FM
#define FM

void makedir(char* name, int debug){
  int result;
  if (stat(name, &sb) == 0 && S_ISDIR(sb.st_mode)){ //checking if directory exists
      printf(KRED"[ERROR]: "KNRM"directory already exists");
      return;
  }

  //dir will contain the folder that will be made
  char* dir = malloc(strlen(name) + strlen(directory) + 1);
  strcpy(dir, directory);
  strcat(dir, name);
  strcat(dir, "/");
  dir[strlen(directory) + strlen(name) + 1] = '\0';

  if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"name = %s \n", name);
  if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"directory = %s \n", dir);

  if((result = mkdir(dir, 0777)) == -1){
    printf(KRED"[ERROR]: couldn't make directory\n\n"KNRM);
    return;
  }
  free(dir);
}

void remdir(char* name, int debug){
  int result;

  //dir = directory of file that will be removed
  char* dir = malloc(strlen(name) + strlen(directory));
  strcpy(dir, directory);
  strcat(dir, name);
  strcat(dir, "/");
  dir[strlen(directory) + strlen(name) + 1] = '\0';

  if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"%s \n", dir);

  if((rmdir(dir)) == -1) printf(KRED"[ERROR]: couldn't delete directory\n\n KNRM");

  if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"%s \n", name);

  free(dir);
}

void cd(char* name, int debug){
  if ((strcmp(name, "..")) == 0){ //if argument pushed was ".." then go back in directory
    int i = strlen(directory) - 2; //go behind the last / in directory string

    for (i; directory[i] != '/'; i--); //find where the second to last / is located
    directory[i + 1] = '\0'; //and next to the / end the string
  }
  else {
    char* path = malloc(strlen(directory) + strlen(name)); //allocate enough memory for path
    strcpy(path, directory); //copy current directory
    strcat(path, name); //put in path string the name of the directory the user wants to change to

    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"path = %s\n", path);

    DIR* dir = opendir(path);

    if (dir) {
        strcpy(directory, path);
        strcat(directory, "/");

        if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"directory = %s \n", directory);
    }
    else {
      printf(KRED"[ERROR]: "KNRM"Directory doesn't exist\n");
    }
    free(path);
  }
}
#endif
