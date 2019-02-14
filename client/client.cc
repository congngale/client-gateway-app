#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

#define PORT 2019
#define BUFFER_LEN 4096
#define HOST "127.0.0.1"

int main(int arg, char *args[]) {
  //init
  int socket_fd = 0;
  char data_buffer[BUFFER_LEN];
  socklen_t server_address_len;
  struct sockaddr_in server_address;

  //clear buffer
  memset(data_buffer, '\0' ,sizeof(data_buffer));
  memset(&server_address, '\0', sizeof(server_address));

  //create socket
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

  cout << "Create socket with status = " << socket_fd << endl;

  //check
  if (socket_fd > 0) {
    //set server info
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(HOST);

    //send request to server
    string request = "Request for new connection";
    sendto(socket_fd, request.c_str(), request.length(), MSG_CONFIRM,
      (const struct sockaddr*) &server_address, sizeof(server_address));

    cout << "Start waiting for response" << endl;

    //receive data from server
    recvfrom(socket_fd, data_buffer, BUFFER_LEN, MSG_WAITALL, 
      (struct sockaddr*) &server_address, &server_address_len);

    cout << "Received data = " << data_buffer << endl;

    close(socket_fd);
  }

  return 0;
}