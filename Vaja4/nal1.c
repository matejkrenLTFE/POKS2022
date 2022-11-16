#include <stdio.h>
#include <pthread.h>

int A = 50;
int B = 20;
int C = 40;
int D = 23;
int E = 12;
int F = 22;

int AB = 0;
int CD = 0;
int EF = 0;

void *fun1();
void *fun2();
void *fun3();

int main() {
   
   pthread_t thread1, thread2 , thread3;
   int R = 0;

   pthread_create(&thread1, NULL, &fun1, NULL);
   pthread_create(&thread2, NULL, &fun2, NULL);
   pthread_create(&thread3, NULL, &fun3, NULL);
   
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
   pthread_join(thread3, NULL);

   R = AB * CD * EF;

   printf("Konec, Rezultat = %d\n", R);
   return(1);
}
void *fun1(){
   AB = A + B;
}
void *fun2(){
   CD = C - D;
}
void *fun3(){
   EF = E + F;
}
