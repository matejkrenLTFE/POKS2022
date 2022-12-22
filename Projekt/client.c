
#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <time.h>

int main(int argc , char *argv[]) {   
    int sock;
	struct sockaddr_in server;
    char buf[1024];
	char exitMSG[1024] = "EXIT";
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1){
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 5095 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");
	
    while(1) {
        printf("Please enter the message: ");
        bzero(buf,1024);
        fgets(buf,1024,stdin);
        printf("Send %s \n", buf);

        if(send(sock, buf, 1024, 0)) 
            perror("Sendto");
        if(strncmp(buf, exitMSG, 4) == 0){
            break;
        }

        if(recv(sock , buf , 1024 , 0)) 
            perror("recvfrom");
        printf("Received a datagram:%s\n ",buf);

        if(strncmp(buf, "EXIT", 4) == 0){
            break;
        }
    }
	
	close(sock);
	return 0;
}
