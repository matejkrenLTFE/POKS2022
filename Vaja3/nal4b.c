#include <stdio.h> 
#include <unistd.h> 

int main() {
   printf("START: Moj pid = %d \n", getpid());
   int PidOtroka = fork();
   if(PidOtroka == 0){ // OTROK
   printf("OTROK: Moj pid = %d PidStarsa = %d PidOtroka = %d\n", getpid(), getppid(), PidOtroka);
   }else{ // STARs
      printf("STARS: Moj pid = %d PidStarsa = %d PidOtroka = %d\n", getpid(), getppid(), PidOtroka);
   }
    sleep(1); 
   return(0); 
}
