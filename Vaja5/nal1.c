#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h>

void fun1();

int main () {
   pthread_t thread1, thread2; 
   char *msg1 = "1";
   char *msg2 = "2";
   pthread_create(&thread1, NULL, (void *) fun1, (void*) msg1); 
   pthread_join(thread1, NULL);
   printf("Konec \n");
   return (1);
}

void fun1(void * ptr) {
  char *msg;
  msg = (char *) ptr;
  int i,j;
  for (i=0; i< 40; i++) {
      printf("Thread %s i=%d ", msg, i ); 
      for (j=0;j<60; j++){
         printf("%s", msg);
      }
   printf("\n");
  }
}
