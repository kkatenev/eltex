#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define SERVER_PORT 8888

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t address_length;
    char buffer[BUFFER_SIZE];

    // Создание сокета
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Привязка сокета к адресу сервера
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Listening on port %d...\n", SERVER_PORT);

    while (1) {
        // Ожидание и чтение сообщения от клиента
        address_length = sizeof(client_address);
        memset(buffer, 0, BUFFER_SIZE);
        if (recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_address, &address_length) < 0) {
            perror("Failed to receive message");
            exit(EXIT_FAILURE);
        }
        printf("Client: %s", buffer);
    }

    // Закрытие сокета
    close(server_socket);

    return 0;
}
