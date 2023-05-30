#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define BROADCAST_PORT 8888

int main() {
    int client_socket;
    struct sockaddr_in client_address, server_address;
    socklen_t address_length;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    memset(&client_address, 0, sizeof(client_address));
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(BROADCAST_PORT);
    client_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) < 0) {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(BROADCAST_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    printf("Broadcast client started. Listening on port %d...\n", BROADCAST_PORT);

    while (1) {
        address_length = sizeof(server_address);
        memset(buffer, 0, BUFFER_SIZE);
        if (recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_address, &address_length) < 0) {
            perror("Failed to receive message");
            exit(EXIT_FAILURE);
        }
        printf("Server: %s", buffer);
    }

    close(client_socket);

    return 0;
}
