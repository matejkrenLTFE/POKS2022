#include <stdio.h> 
#include <unistd.h>

int main() {
	printf("Proces imam: PID = %d PPID = %d\n", getpid(),getppid());
	return(0); 
}
