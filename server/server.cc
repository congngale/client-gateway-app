
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

int main(int arg, char *args[]) {
  //init
  int socket_fd = 0;
  char data_buffer[BUFFER_LEN];
  struct sockaddr_in server_address;

  // creating socket
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  //clear ip struct
  memset(data_buffer, '\0' ,sizeof(data_buffer));
  memset(&server_address, '\0', sizeof(server_address));

  //set server info
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  //binding socket into port and ip address
  bind(socket_fd, (struct sockaddr*)&server_address,
    sizeof(server_address));

  //listen on socket
  listen(socket_fd , MAX_CLIENT);

  cout << "Started server with port " << PORT <<endl;

  //loop
  while(true) {
    //init client structure
    socklen_t client_address_len;
    struct sockaddr_in client_address;

    //clean up memory
    memset(&client_address, '\0', sizeof(client_address));
    memset(&client_address_len, '\0', sizeof(client_address_len));

    //accept connection from all client
    int connection_id = accept(socket_fd, (struct sockaddr*)&client_address,
      &client_address_len);

    //get client ip
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);

    cout << "Client connected with ip = " << client_ip <<endl;

    //read request
    read(connection_id, data_buffer, BUFFER_LEN - 1);
    
    cout << "Client request = " << data_buffer << endl;

    //example data
    string reponse = "Connection request is accepted";

    //send request
    write(connection_id, reponse.c_str(), reponse.length());

    //close connection
    close(connection_id);

    //sleep
    usleep(INTERVAL);
  }
}