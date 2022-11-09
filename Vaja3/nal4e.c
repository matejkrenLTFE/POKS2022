
#include <stdio.h> 
#include <unistd.h> 

int main() {
    printf("START: Moj pid = %d \n", getpid());
    int PidOtroka = fork();
    if(PidOtroka != 0){
        PidOtroka = fork();
        if(PidOtroka != 0){
            PidOtroka = fork();
        }else{ // OTROK
            sleep(10);
            printf("PID otroka je %d.\n", getpid());
            return(1);
        }
    }else{ // OTROK
        sleep(10);
        printf("PID otroka je %d.\n", getpid());
        return(1);
    }
    
    while(!(wait(0) == -1));

    printf("KONEC: Moj pid = %d PidStarsa = %d PidOtroka = %d\n", getpid(), getppid(), PidOtroka);
    sleep(1);
    return 0;
}