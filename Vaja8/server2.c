/* Creates a datagram UDP server.  The port number is passed as an argument. */
/* This server runs forever */

#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>  //ZA niti
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void poslji(void);
void prejmi(void);

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int sock, length, n;
struct sockaddr_in server, from;
socklen_t fromlen;
char buf[1024];

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2;

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(0);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0); /* create new socket */
    if (sock < 0) error("Opening socket");
    length = sizeof(server);
    bzero(&server, length);
    server.sin_family = AF_INET; /* Internet */
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));                 /* port */
    if (bind(sock, (struct sockaddr *)&server, length) < 0) /* bind socket with port */
        error("binding");
    fromlen = sizeof(struct sockaddr_in);

    pthread_create(&thread1, NULL, (void *)poslji, NULL);
    pthread_create(&thread2, NULL, (void *)prejmi, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    close(sock);
    return 0;
}

void poslji(void) {
    char buf[1024];
    while (1) {
        printf("Please enter the message: ");
        bzero(buf, 1024);
        fgets(buf, 1024, stdin);
        printf("Sent %s \n", buf);
        n = sendto(sock, buf, 1024, 0, (struct sockaddr *)&from, fromlen);
        if (n < 0) error("sendto");
        if (buf[0] == 'X') {
            break;
        }
    }
}

void prejmi(void) {
    char buf[1024];
    while (1) {
        n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0) error("recvfrom");
        printf("Received a datagram:%s\n ", buf);
        if (buf[0] == 'X') {
            break;
        }
    }
}