/* Creates datagram UDP client in the internet domain. */
/* IP address and port are passed as argument */
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>  // ZA NITI
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

struct hostent *hp;
int sock, length, n;
struct sockaddr_in server, from;
socklen_t fromlen;

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2;

    if (argc != 3) {
        printf("Usage: client IP port\n");
        exit(1);
    }
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("socket");

    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if (hp == 0) error("Unknown host");
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));
    length = sizeof(struct sockaddr_in);

    pthread_create(&thread1, NULL, (void *)poslji, NULL);
    pthread_create(&thread2, NULL, (void *)prejmi, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    close(sock);
    return 0;
}

void poslji(void) {
    char buf[1024];
    bzero(buf, 1024);
    printf("Send %s \n", buf);
    n = sendto(sock, buf, 1024, 0, (const struct sockaddr *)&server, length);
    if (n < 0) error("Sendto");
    while (1) {
        printf("Please enter the message: ");
        bzero(buf, 1024);
        fgets(buf, 1024, stdin);
        printf("Send %s \n", buf);
        n = sendto(sock, buf, 1024, 0, (const struct sockaddr *)&server, length);
        if (n < 0) error("Sendto");
        if (buf[0] == 'X') {
            break;
        }
    }
}

void prejmi(void) {
    char buf[1024];
    while (1) {
        n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&server, &length);
        if (n < 0) error("recvfrom");
        printf("Received a datagram:%s\n ", buf);
        if (buf[0] == 'X') {
            break;
        }
    }
}
