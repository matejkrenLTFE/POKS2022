#include <stdio.h> 
#include <unistd.h>

int main() {
	printf("Proces ima: PID = %d PPID = %d\n", getpid(),getppid());
	return(0); 
}
