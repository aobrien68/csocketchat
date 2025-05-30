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

//int sockfd;
//char* buffer;
//pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t display_cond = PTHREAD_COND_INITIALIZER;
//pthread_cond_t input_cond = PTHREAD_COND_INITIALIZER;
//int write_time = 0;

/*void* client_thread(void* arg) {
    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(struct sockaddr_in);
    int* fd_add = (int*)arg;
    *fd_add = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if (*fd_add < 0) {
        exit(3);
    }

    char* input_buffer = &buffer[HALF_BUFFER_SIZE];
    char last_message[HALF_BUFFER_SIZE];
    while (1) {
        pthread_mutex_lock(&buffer_lock);
        if (write_time) {
            pthread_cond_signal(&display_cond);
            pthread_cond_wait(&input_cond, &buffer_lock);
        } else {
            if (0 >= read(*fd_add, input_buffer, HALF_BUFFER_SIZE-1)) {
                exit(4);
            }
            input_buffer[HALF_BUFFER_SIZE-1] = '\0';
            if (strcmp(last_message, input_buffer) != 0) {
                strcpy(last_message, input_buffer);
                write_time = 1;
            }
        }
        pthread_mutex_unlock(&buffer_lock);
    }
}*/

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }
    int port = atoi(argv[1]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

    //pthread_t threads[MAX_USERS];
    int cli_fds[MAX_USERS];
    char* buffer = malloc(PARTIAL_BUFFER_SIZE * MAX_USERS);
    char* cache = malloc(PARTIAL_BUFFER_SIZE * MAX_USERS);
    /*afor(int i=0; i<MAX_USERS; i++) {
        pthread_create(&threads[i], NULL, client_thread, &cli_fds[i]);
    }*/

    while (1) {
        //pthread_mutex_lock(&buffer_lock);
        //pthread_cond_wait(&display_cond, &buffer_lock);
        for (int i=0; i<MAX_USERS; i++) {
            read(cli_fds[i], &buffer[i * PARTIAL_BUFFER_SIZE], PARTIAL_BUFFER_SIZE);
            
            write(cli_fds[i], buffer[], PARTIAL_BUFFER_SIZE);
        }
        //write_time = 0;
        //pthread_cond_signal(&input_cond);
        //pthread_mutex_unlock(&buffer_lock);
    }
}
