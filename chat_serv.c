#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAX_USERS (2)
#define PARTIAL_BUFFER_SIZE (256) 
#define SLEEP_TIME (100000)

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

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
        return 3;
    }

    listen(sockfd, MAX_USERS);

    fd_t* cli_fds[] = calloc(5 * sizeof(fd_t));
    char* true_buffer = calloc(2 * BUFFER_SIZE);
    char* cache = malloc(BUFFER_SIZE);

    while (1) {
        for (int i=0; i<MAX_USERS; i++) {
            
            if (cli_fd[i] && read(cli_fds[i], true_buffer, (2 * BUFFER_SIZE) - 1) > 0
            && strcmp(&true_buffer[BUFFER_SIZE], "")) { // New msg put in input half of buffer
                strcpy(cache, &true_buffer[BUFFER_SIZE]); // new msg put in cache
                for (int j=0; j<MAX_USERS; j++) {
                    if (cli_fd[j] && read(cli_fds[j], true_buffer, (2 * BUFFER_SIZE) - 1) > 0) { // New msg put in display half of buffer
                        if (i == j) {
                            memset(&true_buffer[BUFFER_SIZE], 0, BUFFER_SIZE); // Signal msg was read
                        }
                        while ()
                        write(cli_fd[i], true_buffer, BUFFER_SIZE); // Write msg to display socket
                    }
                }
                usleep(SLEEP_TIME);
            }
        }
    }
}
