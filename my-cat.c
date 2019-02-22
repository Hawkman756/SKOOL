#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv){
for(int c = 1; argv[c]!=NULL; c++){
  char Data[1000];
  FILE * fp;
  fp = fopen (argv[c], "r");
  if (fp == NULL) {
   printf("my-cat cannot open file %s\n", argv[c]);
   exit(0);
  }
while (true){
  fgets(Data, 1000, fp);
  if(feof(fp)) break;
  printf("%s", Data);
}

 fclose(fp);
}

 return 0;
}
