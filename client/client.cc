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
  struct sockaddr_in server_address;

  //clear buffer
  memset(data_buffer, '\0' ,sizeof(data_buffer));

  //create socket
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  cout << "Create socket result = " << socket_fd << endl;

  //check
  if (socket_fd > 0) {
    //set server info
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(HOST);

    //connect to server
    int status = connect(socket_fd, (struct sockaddr *)&server_address,
      sizeof(server_address));

    cout << "Connection status = " << status << endl;

    //check
    if (status == 0) {
      //send connect request
      string request = "Request for new connection";
      write(socket_fd, request.c_str(), request.length());

      //read data
      int len = read(socket_fd, data_buffer, BUFFER_LEN - 1);

      //read data
      while(len > 0) {
        cout << "Received data = " << data_buffer << endl;

        //read data
        len = read(socket_fd, data_buffer, BUFFER_LEN - 1);
      }
    }
  }
}