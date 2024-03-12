//
// Created by Noe Steiner on 12/03/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_PENDING 5

int main() {
    int server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int bind_result = bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_result < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while (1) {
        char buffer[1024];
        ssize_t n = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_addr, &client_len);
        if (n > 0) {
            printf("Received: %s\n", buffer);
            break;
        }
    }

    close(server_fd);
    return 0;
}