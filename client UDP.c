#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


#define PORT 8080
#define IP_ADDRESS "127.0.0.1"
#define BUFFER_SIZE 1024

// Declare the wait_for_ack function prototype if it's defined elsewhere
void wait_for_ack(int sockfd) {
    // Example implementation (you can adjust it based on your need)
    printf("Waiting for acknowledgment... \n");
    sleep(1);  // Simulate waiting for acknowledgment
}

int main(){
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE] = {0};
    char ack[BUFFER_SIZE] = {0};  // Declare the ack buffer
    int sock_fd;
  
    // Create socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    // Prepare the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);  // Ensure correct byte order for port
    if(inet_pton(AF_INET, IP_ADDRESS, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    // Remove the unnecessary connect() for UDP
    // No need for connect() with UDP socket. You can use sendto() instead.

    printf("Client connected to server\n");
    
    int retry_count = 0; 
    while(1) {
        printf("Enter the message to send: ");
        scanf("%s", message);

        // Send the message to the server
        if (sendto(sock_fd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }
        printf("Message sent\n");

        wait_for_ack(sock_fd);

        // Receive acknowledgment from server
        socklen_t len = sizeof(server_addr);
        int n = recvfrom(sock_fd, ack, sizeof(ack), 0, (struct sockaddr *)&server_addr, &len);
        if(n > 0) {
            ack[n] = '\0';  // Null-terminate the received data
            printf("Received response: %s\n", ack);

            if(rand()%2) {
                printf("Client simulated ACK loss\n");
                retry_count++;
                continue;
            }
            if(strcmp(ack, "ACK") == 0) {
                break;
            }
        } else {
            retry_count++;
            printf("No ACK received, retrying %d\n", retry_count);
        }

        if(retry_count >= 3) {
            printf("Retried maximum amount of times, exiting\n");
            break;
        }
    }

    // Close the socket
    close(sock_fd);
    return 0;
}

