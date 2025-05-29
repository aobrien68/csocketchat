#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFFER_SIZE (256)

void* write_thread(void* arg) {

}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int port = atoi(argv[2]);

    int clifd = (AF_INET, SOCK_STREAM, 0);
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

    if (connect(clifd, &serv_addr, sizeof(struct sockaddr_in)) < 0) {
        return 4;
    }

    while (1) {

    }
}
