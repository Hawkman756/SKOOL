#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#define delimiter " \t\r\n\a"


void errorFunc(){
 char error_message[30] = "An error has occurred\n";
 write(STDERR_FILENO, error_message, strlen(error_message));
 exit(0);//to kill the child process that threw the error
}
int main(){

  while(true){
   char *comlin = NULL;
   size_t size = 0;
   int sitch = 0;
   char **argStore = malloc(64 * sizeof(char));
   char *arguments;
   int counter = 0;
   int pathInst = 0;
   const char cd[10] = "cd";
   char *builtInComms[] = {"cd", "exit", "path"};
   pid_t processNum;
   int allow = 0;


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
   argStore[counter] = '\0';
    //builtin commands
   if(strstr(argStore[0], cd) != NULL){
      chdir(argStore[1]);
      allow = 1;
   }
   if(strcmp(builtInComms[1], argStore[0])==0){
      exit(0);
   }
   if(strcmp(builtInComms[2], argStore[0])==0){
       pathInst = 1;
       chdir(argStore[1]);
   }
   if(allow == 0){ //execution of commands
      processNum = fork();
      if(processNum == 0){
       if(pathInst != 1){
        if(execvp(argStore[0], argStore) == -1){ errorFunc();}
       }
       else if(execv(argStore[1], argStore)== -1){ errorFunc();}
      }
      if(processNum < 0) { errorFunc();}
      else{
             waitpid(processNum, &sitch, WUNTRACED);
         while(!WIFSIGNALED(sitch) && !WIFEXITED(sitch))
           {
                waitpid(processNum, &sitch, WUNTRACED);
           }
      }
     //emptying for reuse
    free(comlin);
    free(argStore);
   }
  }
  return 0;
}
