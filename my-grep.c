#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int main(int argc, char **argv){
  FILE * pfile;
  if(argv[1] == NULL && argv[2] == NULL){
   printf("my-grep: searchterm [file ...]\n");
   exit(1);
  }
  if((fopen(argv[2], "r")) == NULL){
    printf("my-grep: cannot open file\n");
    exit(1);
  }
  pfile = fopen(argv[2], "r");
  char a1[500];
while (true){
  if(feof(pfile)) break;
  fgets(a1, sizeof(a1), pfile);
  if(strstr(a1, argv[1])){
     printf("%s", a1);
  }
}

 fclose(pfile);

 return 0;
}
