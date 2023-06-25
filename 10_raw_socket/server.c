#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t address_length;
    char buffer[BUFFER_SIZE];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }


    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);
    server_address.sin_addr.s_addr = INADDR_ANY;


    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }


    if (listen(server_socket, 1) < 0) {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Listening on port 80...\n");

    address_length = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_length);
    if (client_socket < 0) {
        perror("Failed to accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            perror("Failed to receive data");
            exit(EXIT_FAILURE);
        } else if (bytes_received == 0) {
            printf("Client disconnected.\n");
            break;
        }


        printf("Received: %s", buffer);
    }


    close(client_socket);
    close(server_socket);

    return 0;
}
