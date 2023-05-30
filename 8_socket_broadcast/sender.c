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
    int server_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    int broadcast_permission = 1;

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Разрешение широковещательной отправки
    if (setsockopt(server_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_permission, sizeof(broadcast_permission)) < 0) {
        perror("Failed to set socket options");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(BROADCAST_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    printf("Broadcast server started. Broadcasting on port %d...\n", BROADCAST_PORT);

    while (1) {
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        if (sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            perror("Failed to send message");
            exit(EXIT_FAILURE);
        }
    }

    close(server_socket);

    return 0;
}
