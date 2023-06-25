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
    int raw_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    
 
    raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (raw_socket < 0) {
        perror("Failed to create raw socket");
        exit(EXIT_FAILURE);
    }
    
 
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80); 
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Raw client started.\n");

    while (1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        
        if (strcmp(buffer, "quit\n") == 0) {
            break;
        }
        
        if (sendto(raw_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            perror("Failed to send packet");
            exit(EXIT_FAILURE);
        }
    }

    close(raw_socket);

    return 0;
}
