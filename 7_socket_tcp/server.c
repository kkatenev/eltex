#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t address_length;
    char buffer[BUFFER_SIZE];

    // Создание сокета
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8888);

    // Привязка сокета к адресу сервера
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    // Ожидание подключения клиента
    if (listen(server_socket, 1) < 0) {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Listening on port 8888...\n");

    // Принятие подключения от клиента
    address_length = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_length);
    if (client_socket < 0) {
        perror("Failed to accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    while (1) {
        // Чтение сообщения от клиента
        memset(buffer, 0, BUFFER_SIZE);
        if (read(client_socket, buffer, BUFFER_SIZE) <= 0) {
            break;
        }
        printf("Client: %s", buffer);

        // Отправка ответного сообщения клиенту
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(client_socket, buffer, strlen(buffer));
    }

    // Закрытие сокетов
    close(client_socket);
    close(server_socket);

    return 0;
}
