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

  if((rmdir(dir)) == -1) printf(KRED"[ERROR]: "KNRM"couldn't delete directory\n");

  if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"%s \n", name);

  free(dir);
}

void cd(char* name, int debug){
  if ((strcmp(name, "..")) == 0){ //if argument pushed was ".." then go back in directory
    //so that the program doesn't cause a segmentation fault
    if ((strcmp(directory, "./root/")) == 0){
      printf(KRED"[ERROR]: "KNRM"Can't go back (you are in the root directory)\n");
    }
    else {
      int i = strlen(directory) - 2; //go behind the last / in directory string

      for (i; directory[i] != '/'; i--); //find where the second to last / is located
      directory[i + 1] = '\0'; //and next to the / end the string
    }
  }
  else if ((strcmp(name, ".")) == 0){/*don't do anything lol*/} // . is a folder in linux
  else {
    char* path = malloc(strlen(directory) + strlen(name)); //allocate enough memory for path
    strcpy(path, directory); //copy current directory
    strcat(path, name); //put in path string the name of the directory the user wants to change to

    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"path = %s\n", path);

    DIR* dir = opendir(path);

    if (dir) {
        strcpy(directory, path); //change the directory string (located in boot.h)
        strcat(directory, "/");

        if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"directory = %s \n", directory);
    }
    else {
      printf(KRED"[ERROR]: "KNRM"Directory doesn't exist\n");
    }
    free(path);
    closedir(dir);
  }
}

//this code is a slightly modified version of gnu's example:
//https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html
void ls(int debug){
  DIR* dir = opendir(directory);
  char* path;
  struct dirent *ep;

  if (dir != NULL){ //if directory have anything at all (impossible)
    while (ep = readdir(dir)) { //read every file
      path = malloc(strlen(directory) + strlen(ep -> d_name) + 1); //allocate enough memory for path string
      strcpy(path, directory); //make string (directory + name of folder + end string char)
      strcat(path, ep -> d_name);
      strcat(path, "\0");

      if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"path: %s\n", path); //for debug to check what path string is

      //put file/folder in the struct stat sb (located in boot.h)
      stat(path, &sb);

      if (S_ISDIR(sb.st_mode) != 0){ //check if it is a regular directory
        printf(KYEL"%s\n"KNRM, ep -> d_name);
      }
    }

    //we have to refresh variables so that the scan can work again
    free(ep);
    closedir(dir);

    struct dirent *ep;
    DIR* dir = opendir(directory);

    while (ep = readdir(dir)) { //read every file
      path = malloc(strlen(directory) + strlen(ep -> d_name) + 1); //allocate enough memory for path string
      strcpy(path, directory); //make string (directory + name of file + end string char)
      strcat(path, ep -> d_name);
      strcat(path, "\0");

      if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"path: %s\n", path); //for debug to check what path string is

      //put file/folder in the struct stat sb (located in boot.h)
      stat(path, &sb);

      if (S_ISREG(sb.st_mode) != 0){ //check if it is a regular file
        printf(KBLU"%s\n"KNRM, ep -> d_name);
      }
    }
  }
  else {
    printf(KRED"[ERROR]: "KNRM"Can't find any folders/files"); //if error
  }
  //free allocated memory
  free(path);
  free(ep);

  closedir(dir);
  printf("\n");//new line so that it doesn't look weird
}
#endif
