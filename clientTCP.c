//
// Created by Noe Steiner on 05/03/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_ADDR "127.0.0.1"
#define PORT 8080

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);

    int connect_result = connect(client_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (connect_result < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (1) {
        char buffer[1024];
        sprintf(buffer, "Hello, server! %d", i++);
        ssize_t n = write(client_fd, buffer, strlen(buffer));
        if (n < 0) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        memset(buffer, 0, sizeof(buffer));
        n = read(client_fd, buffer, sizeof(buffer) - 1);
        if (n < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Received: %s\n", buffer);
    }
    close(client_fd);
    return 0;
}
