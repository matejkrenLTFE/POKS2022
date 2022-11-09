#include <stdio.h>
#include <pthread.h>

void *fun1();

/* pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; */

main()
{
   pthread_t thread1, thread2;

 /* Kreiraj 2 samostojni niti, ki izvajata funkcijoC*/

   pthread_create(&thread1, NULL, &fun1, NULL);
   
 /* Počakaj da se niti izvršita preden nadaljuješ s funkcijo main() */

   pthread_join(thread1, NULL);
      
   printf("Konec, Rezultat = ");
   return(1);
}

void *fun1()
{

   /* pthread_mutex_lock (&mutex1); */
   /* vsebina niti */
   /* pthread_mutex_unlock (&mutex1); */

}
