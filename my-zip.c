#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*void appender(char x, char y){
 int leng =strlen(x);
 x[leng] = y;
 x[leng+1] = '\0';
}*/
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
memset(append, '\0', (sizeof(string)/sizeof(char)));
for(a = 0; string[a] != '\0'; a++){ //change back to string[a]!='\0'
  if(string[a] == string[a+1]){
    c++;
  }
  else{
       printf("%d" , c);
       strcpy(append[v], (char) c); //find a way to put values into the array
       //append[v] =(char) c;
       strcpy(append[v+1], string[a]);
       c = 1;
       printf("%c" ,append[v]);
       v+=2;
  }
}

fp = fopen("testzippy.z", "w");
fwrite(append, 5, a, fp);
fclose(fpoint);
fclose(fp);

return 0;
}
