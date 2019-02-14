
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

#define PORT 2019
#define MAX_CLIENT 100
#define BUFFER_LEN 4096
#define INTERVAL 100000 //sleep for 100 miliseconds
#define HOST "127.0.0.1"

int main(int arg, char *args[]) {
  //init
  int socket_fd = 0;
  char data_buffer[BUFFER_LEN];
  struct sockaddr_in server_address;

  // creating socket
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

  //clear ip struct
  memset(data_buffer, '\0' ,sizeof(data_buffer));
  memset(&server_address, '\0', sizeof(server_address));

  //set server info
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  //binding socket into port and ip address
  bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address));

  cout << "Started server with port " << PORT <<endl;

  //loop
  while(true) {
    //init client structure
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    //clean up memory
    memset(&client_address, '\0', sizeof(client_address));

    //receive data from client
    recvfrom(socket_fd, data_buffer, BUFFER_LEN, MSG_WAITALL, 
      (struct sockaddr*) &client_address, &client_address_len);

    //get client ip
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);

    cout << "Client connected with ip = " << client_ip <<endl;
    
    cout << "Client request = " << data_buffer << endl;

    //example data
    string reponse = "Connection request is accepted";

    //send response
    sendto(socket_fd, reponse.c_str(), reponse.length(), MSG_CONFIRM,
      (const struct sockaddr*) &client_address, client_address_len);
  }

  return 0;
}