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

    char* buffer = calloc(1, 256);
    buffer[255] = '\0';

    fd_t clifd = accept(sockfd, (struct sockaddr*)&serv_addr, (socklen_t*)&socklen);
    if (clifd < 0) {
        return 4;
    }

    /*while (read(clifd, buffer, 255) > 0) {
        if (*buffer) {
            usleep(SLEEP_TIME);
        } else {
            printf("%s\n", buffer);
            buffer[0] = '\0';
            if (write(clifd, buffer, 256) < 0) {return 5;}
        }
    }*/
    write(clifd, buffer, 256);
    printf("Entering Loop\n");
    while (read(clifd, buffer, 256) > 0) {
        printf("Before Print\n");
        printf("%s\n", buffer);
        printf("After Print\n");
        usleep(SLEEP_TIME);
    }
    printf("End: %s", buffer);
}
