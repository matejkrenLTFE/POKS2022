#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h>

void fun1();
sem_t semid;

int main () {
   pthread_t thread1, thread2; 
   char *msg1 = "1";
   char *msg2 = "2";

   sem_init(&semid, 1, 1);

   pthread_create(&thread1, NULL, (void *) fun1, (void*) msg1); 
   pthread_create(&thread2, NULL, (void *) fun1, (void*) msg2); 

   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);

   printf("Konec \n");
   return (1);
}

void fun1(void * ptr) {
  char *msg;
  msg = (char *) ptr;

  int i,j;
  int b;
  for (i=0; i< 40; i++) {
      
      sem_wait(&semid);

      printf("Thread %s i=%d ", msg, i ); 

      for (j=0;j<60; j++){
         printf("%s", msg);
         for(b=0; b < 1000000; b++){                // PRIBLIŽNO 1M ~ 1s
            int a = 100*54/1232*1231322/544 - 11;
         }
      }
      printf("\n");
      
      sem_post(&semid);


      for(b=0; b < 10000000; b++){                // PRIBLIŽNO 1M ~ 1s
         int a = 100*54/1232*1231322/544 - 11;
      }
  }
}
