#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
  int sockfd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_len = sizeof(client_addr);
  char buffer[BUFFER_SIZE];

  // Create socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  printf("Socket created successfully\n");

  // Setup server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Bind the socket to the server address
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("bind failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d\n", PORT);

  // Server loop to receive messages
  while (1) {
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
    if (n < 0) {
      perror("Failed to receive data");
      close(sockfd);
      exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';  // Null-terminate the received string
    printf("Message received: %s\n", buffer);

    // Response message
    char *response = "Message received";

    // Send response back to client
    if (sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, addr_len) < 0) {
      perror("Failed to send response");
      close(sockfd);
      exit(EXIT_FAILURE);
    }
  }

  // Close socket (though this won't be reached in this infinite loop)
  close(sockfd);
  return 0;
}

