/* Creates datagram UDP client in the internet domain. */
/* IP address and port are passed as argument */

int main(int argc, char *argv[]) {
    struct hostent *hp;

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

    printf("Please enter the message: ");
    bzero(buf, 1024);
    fgets(buf, 1024, stdin);
    printf("Send %s \n", buf);
    n = sendto(sock, buf, 1024, 0, (const struct sockaddr *)&server, length);
    if (n < 0) error("Sendto");

    close(sock);
    return 0;
}
