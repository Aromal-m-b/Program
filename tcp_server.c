#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "Hello World Received";

    printf("Server is Listening.....\n");

    // Socket creation
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket Failed");
        exit(EXIT_FAILURE);
    }

    // Binding
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding Failed");
        exit(EXIT_FAILURE);
    }
    printf("Bind completed\n");

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d...\n", PORT);

    // Accept connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Connection accepted\n");

    // Read message from client
    valread = read(new_socket, buffer, BUFFER_SIZE);
    printf("Received message from client: %s\n", buffer);

    // Send response to client
    send(new_socket, hello, strlen(hello), 0);
    printf("Response sent to client\n");

    // Close socket
    close(new_socket);
    return 0;
}

