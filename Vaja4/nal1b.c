#include <stdio.h>
#include <pthread.h>

struct arg_struct {
    int arg1;
    int arg2;
};

void *fun1();
void *fun2();
void *fun3();

int main() {
   
   pthread_t thread1, thread2 , thread3;
   int R = 0;
   int AB, CD, EF;
    struct arg_struct args1, args2, args3;
    args1.arg1 = 50;
    args1.arg2 = 20;
    args2.arg1 = 40;
    args2.arg2 = 23;
    args3.arg1 = 12;
    args3.arg2 = 22;

   pthread_create(&thread1, NULL, &fun1, (void *)&args1);
   pthread_create(&thread2, NULL, &fun2, (void *)&args2);
   pthread_create(&thread3, NULL, &fun3, (void *)&args3);
   
   pthread_join(thread1, (void **)&AB);
   pthread_join(thread2, (void **)&CD);
   pthread_join(thread3, (void **)&EF);

   R = AB * CD * EF;

   printf("Konec, Rezultat = %d\n", R);
   return(1);
}
void *fun1(void * arguments){
    struct arg_struct *args  = arguments;
    int AB = (args -> arg1) + (args -> arg2);
    pthread_exit((void *)AB);
}
void *fun2(void * arguments){
    struct arg_struct *args  = arguments;
   int CD = (args -> arg1) - (args -> arg2);
   pthread_exit((void *)CD);
}
void *fun3(void * arguments){
    struct arg_struct *args  = arguments;
   int EF = (args -> arg1) + (args -> arg2);
   pthread_exit((void *)EF);
}
