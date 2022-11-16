#include <stdio.h>
#include <pthread.h>

void *fun1();

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int stevec = 0;


int main() {
   pthread_t thread1, thread2;

 /* Kreiraj 2 samostojni niti, ki izvajata funkcijoC*/

   pthread_create(&thread1, NULL, &fun1, NULL);
   pthread_create(&thread2, NULL, &fun1, NULL);
   
 /* Počakaj da se niti izvršita preden nadaljuješ s funkcijo main() */

   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
      
   printf("Konec, Rezultat = %d\n", stevec);
   return(1);
}

void *fun1(){
  int stevecPOM;
  int i, n;
  for( i = 0; i < 2000; i++){
    pthread_mutex_lock(&mutex1);

    stevecPOM = stevec;
    stevecPOM++;
    // ZAKASNITEV
    for (n = 0; n < 1000; n++){
      int a  = 2*32*3123123123/532;
    }
    stevec = stevecPOM;
    pthread_mutex_unlock(&mutex1);
  }

}
