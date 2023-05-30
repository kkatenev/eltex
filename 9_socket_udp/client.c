#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // Создание сокета
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(server_address.sin_addr)) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    printf("Client started. Enter 'quit' to exit.\n");

    while (1) {
        // Чтение сообщения для отправки
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Проверка на выход
        if (strcmp(buffer, "quit\n") == 0) {
            break;
        }

        // Отправка сообщения серверу
        if (sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            perror("Failed to send message");
            exit(EXIT_FAILURE);
        }
    }

    // Закрытие сокета
    close(client_socket);

    return 0;
}
