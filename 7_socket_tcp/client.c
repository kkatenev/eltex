#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // Создание сокета
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);

    if (inet_pton(AF_INET, "127.0.0.1", &(server_address.sin_addr)) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // Установка соединения с сервером
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    while (1) {
        // Отправка сообщения серверу
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(client_socket, buffer, strlen(buffer));

        // Чтение ответного сообщения от сервера
        memset(buffer, 0, BUFFER_SIZE);
        if (read(client_socket, buffer, BUFFER_SIZE) <= 0) {
            break;
        }
        printf("Server: %s", buffer);
    }

    // Закрытие сокета
    close(client_socket);

    return 0;
}
