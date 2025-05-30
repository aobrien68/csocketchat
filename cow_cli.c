#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define SLEEP_TIME (100000)

typedef int fd_t;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int port = atoi(argv[2]);

    fd_t clifd = socket(AF_INET, SOCK_STREAM, 0);
    if (clifd < 0) {
        return 2;
    }

    struct hostent* host = gethostbyname(argv[1]);
    if (!host) {
        return 3;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    memcpy(host->h_addr, &serv_addr.sin_addr.s_addr, sizeof(host->h_addr));
    serv_addr.sin_port = htons(port);

    char* buffer = malloc(256);

    if (connect(clifd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr_in))) {
        return 4;
    }

    usleep(SLEEP_TIME);
    while (fgets(buffer, 256, stdin) > 0) {
        buffer[255] = '\0';
        if (write(clifd, buffer, 256) < 0) {return 5;}
    }
}
