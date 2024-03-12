//
// Created by Noe Steiner on 12/03/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define SERVER_ADDR "127.0.0.1"
#define PORT 8080

int main() {
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);

    char buffer[1024];
    time_t now = time(0);
    char* dt = ctime(&now);
    sprintf(buffer, "%s", dt);

    socklen_t server_len = sizeof(server_addr);
    ssize_t n = sendto(client_fd, buffer, strlen(buffer), 0, (struct sockaddr *) &server_addr, server_len);
    if (n < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    close(client_fd);
    return 0;
}
