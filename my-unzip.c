#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv){
FILE *fpoint = fopen(argv[1], "r");
FILE *fp;
char string[100];
char append[100];
int a = 0;
int c = 0;
int v = 1;

while(true){
if(feof(fpoint))
break;

string[a] = fgetc(fpoint);
a++;
}
for(a = 0; string[a]!= '\0'; a+=2){
 for(c = 0; c < (int)string[a]; c++){
  append[c] = string[v];
 }
 v+=2;
}

fp = fopen("unzipped.txt", "w");
fwrite(append, 5, a, fp);
fclose(fpoint);
fclose(fp);

return 0;
}
