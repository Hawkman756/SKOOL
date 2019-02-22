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
int v = 0;

while(true){
if(feof(fpoint))
break;

string[a] = fgetc(fpoint);
a++;
}
for(a = 0; string[a]!= '\0'; a++){
  if(string[a] == string[a+]){
    c++;
  }
  else{
       c++;
       append[v] =(char) c;
       append[v+1] = string[a];
       c = 0;
  }
}

fp = fopen("testzippy.z", "w");
fwrite(append, 5, sizeof(append), fp);
fclose(fpoint);
fclose(fp);

return 0;
}
