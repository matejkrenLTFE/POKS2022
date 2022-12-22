#include <arpa/inet.h>  //inet_addr
#include <pthread.h>    //for threading , link with lpthread
#include <stdio.h>
#include <stdlib.h>  //strlen
#include <stdlib.h>
#include <string.h>  //strlen
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>  //write
#include <uuid/uuid.h>

// the thread function
void *connection_handler(void *);
void *test_handler(void *);

// TODO nastavi globalne spremenljivke in morebitne globalne funkcije

int main(int argc, char *argv[]) {
    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5095);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
        puts("Connection accepted");

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;

        if (pthread_create(&sniffer_thread, NULL, connection_handler, (void *)new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
        puts("Handler assigned");

        // Now join the thread , so that we dont terminate before the thread
        // pthread_join(sniffer_thread , NULL);
    }

    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc) {
    // Get the socket descriptor
    int sock, length, n;
    struct sockaddr_in server, from;
    socklen_t fromlen;
    char buf[1024];
    sock = *(int *)socket_desc;
    fromlen = sizeof(struct sockaddr_in);

    // TODO nastavi spremenljivke za posamezen socket

    while (1) {
        n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0) {
            perror("recvfrom");
        }

        // TODO: Vstavi kodo iz drugega dela
    }
    close(sock);

    return 0;
}