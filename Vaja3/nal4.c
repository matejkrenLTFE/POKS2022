#include <stdio.h> 
#include <unistd.h> 

int main() {
   printf("START: Moj pid = %d \n", getpid());
   int PidOtroka = fork();
   printf("KONEC: Moj pid = %d PidStarsa = %d PidOtroka = %d\n", getpid(), getppid(), PidOtroka);
   sleep(1); 
   return(0); 
}
