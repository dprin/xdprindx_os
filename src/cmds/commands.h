#ifndef COMMANDS
#define COMMANDS

void doCommand(char* command, int debug){
  if ((strcmp(command,"test")) == 0) printf("TESTING\n");
}

void getInput(int debug){
  char* input = malloc(sizeof(char) * 2560);
  char* cdir = malloc(sizeof(char) * 256); //current directory
  int inputSpaces = 0;

  //i'll make a function later that can get the current directory
  strcpy(cdir,directory); //so it wont be included in this current update

  printf("%s> ", username);
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

  if (strlen(input) != 0){ //cause sometimes it is annoying :v
    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"user entered: \"%s\" \n",input);
    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"caSpaces = %i \n", caSpaces);
  }

  doCommand(input, debug);

  caSpaces = 0;

  free(input);
  free(cdir);
}

#endif
