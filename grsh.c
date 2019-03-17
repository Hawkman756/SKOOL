#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#define delimiter "\t\r\n\a"


void errorFunc(){
 char error_message[30] = "An error has occurred\n";
 write(STDERR_FILENO, error_message, strlen(error_message));
}
int main(){

  while(1){
   char *comlin = NULL;
   size_t size = 0;
   size_t malSize = 64;
   int sitch = 0;
   char **argStore = malloc(malSize);
   char *arguments;
   int counter = 0;
   pid_t processNum;


   printf("grsh> ");
   //read Line
   getline(&comlin, &size, stdin);
   //split into seperate arguments
    arguments = strtok(comlin, delimiter);
    while(arguments != NULL) {
      //stores string arguments
      argStore[counter] = arguments;
      counter++;
      //accounts for the NULL value from the strtok
      arguments = strtok(NULL, delimiter);
    }
    //builtin commands
    if(strcmp("cd", argStore[0])==0){
      chdir (argStore[1]);
    }
    if(strcmp("exit", argStore[0])==0){
      exit(0);
    }
    //execution of commands
    else {
      processNum = fork();
      if(processNum == 0){
       if(execvp(argStore[0], argStore) == -1){ errorFunc();}
      }
      if(processNum < 0) {errorFunc();}
      else{
         while(!WIFSIGNALED(sitch) && !WIFEXITED(sitch))
           {
                waitpid(processNum, &sitch, WUNTRACED);
           }
      }
    }
    //emptying for reuse
    free(comlin);
    free(argStore);
  }

  return 0;
}
