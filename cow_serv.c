#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef fd_t = int;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    int port = atoi(argv[1]);

    fd_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return 2;
    }

    struct sockaddr_in serv_addr;
    int socklen = sizeof(struct sockaddr_in);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
        return 3;
    }

    listen(sockfd, 1);

    char* buffer = malloc(256);
    buffer[255] = '\0';

    fd_t clifd = accept(sockfd, &serv_addr, &socklen);
    if (clifd < 0) {
        return 4;
    }

    while (1) {
        if (read(clifd, buffer, 255) <= 0) {
            break;
        }
        printf("%s\n", buffer);
        memset(buffer, 0, 255);

    }
}
