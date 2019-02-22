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
int c = 1;
int v = 0;

while(true){
if(feof(fpoint))
break;

string[a] = fgetc(fpoint);
printf("%c", string[a]);
a++;
}
for(a = 0; string[a] != '\0'; a++){
  if(string[a] == string[a+1]){
    c++;
  }
  else{
       printf("%d" , c);
       append[v] = (char) c;
       append[v+1] = string[a];
       c = 1;
       printf("%c" ,append[v]);
       v+=2;
  }
}

fp = fopen("testzippy.z", "w");
fwrite(string, 5, (a-1), fp);
fclose(fpoint);
fclose(fp);

return 0;
}
