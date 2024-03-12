#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_PENDING 5

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

    int listen_result = listen(server_fd, MAX_PENDING);
    if (listen_result < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

    while (1) {
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        char buffer[1024];
        ssize_t n = read(client_fd, buffer, sizeof(buffer));
        if (n > 0) {
            printf("Received: %s\n", buffer);
            write(client_fd, "Hello, world!", 14);
        }
        if (buffer[0] == 'q') {
            break;
        }
    }

    close(server_fd);
    return 0;
}
