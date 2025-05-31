#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SLEEP_TIME (100000)

typedef int fd_t;

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

    fd_t clifd = accept(sockfd, (struct sockaddr*)&serv_addr, (socklen_t*)&socklen);
    if (clifd < 0) {
        return 4;
    }

    while (read(clifd, buffer, 256) > 0) {
        buffer[255] = '\0';
        printf("%s", buffer);
    }
}
