#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

pthread_cond_t* cond = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int thredNum;

void *threadZip(void *argument){//changes when I call the argument with the buffer, why??
 //printf("Void");//does trigger
 int count = 0;
 char *input = (char*) argument;
 char currentChar;
 int lengthOfbuff = sizeof(input);
// printf("%d \n", lengthOfbuff);
// printf("%s \n", input);
// int loadLen = lengthOfbuff/thredNum;
 int cnt[100];
 char chr[100];
 char previousChar = input[1];
 FILE *fpoint = fopen("hw4.zip", "w");
 for(int py=0; py<lengthOfbuff;py++){
  //printf("triggy");
   currentChar = input[py];
   if(currentChar == previousChar){
    count++;
   }
   else{
     // printf("%d\n", count);
     // printf("%d\n", previousChar);
     cnt[0] =count;
     chr[0] =previousChar;
    fwrite(cnt, sizeof(cnt), 1, fpoint);
    fwrite(chr, sizeof(chr), 1, fpoint);
    count=0;
   }
   previousChar = currentChar;
 }
 fclose(fpoint);
 //fclose(fp);
 return NULL;
}

char* mappy(char *in){
 unsigned char *f;
 int size;
 struct stat s;
 const char * file_name = in;
 int fd = open(file_name, O_RDONLY);

 int status = fstat (fd, & s);
 size = s.st_size;

 f = (unsigned char *)mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
 for (int p = 0; p < size; p++){
    char c;
    c = f[p];
    putchar(c);
 }
 printf("%d\n", status);
 return (char*)f;
}

int main(int argc, char *argv[]){
 char* buffy[argc];
 for(int ap =2; ap < argc; ap++){

  buffy[ap-2] = mappy(argv[ap]);
 }//int b =sizeof(buffy);
// printf("%s\n", buffy[0]);
// printf("%s\n", buffy[1]);

 pthread_t *threads;
 //carry = (char*) malloc(100 * sizeof(char));//may fail
 //iarry = (int*) malloc(100 * sizeof(int));//may need to realloc both
 thredNum = atoi(argv[1]);
// cond = (pthread_cond_t*)malloc(sizeof(pthread_cond_t) * thredNum);
 //arr = (int*)malloc(sizeof(int) * thredNum);//added
 threads = (pthread_t *) malloc(thredNum * sizeof(pthread_t));//memory for threads
 for(int c = 0; c < thredNum; c++){
  //printf("FOUR");
  if(pthread_create (&threads[c], NULL, threadZip, buffy)!=0){
   perror("Can't create thread");
   free(threads);
   exit(-1);
  }
 }
 for(int i =0; i < thredNum; i++){
  pthread_join (threads[i], NULL);
 }

// fclose(fp);
// printf("%d", thStat);
 return 0;
}
