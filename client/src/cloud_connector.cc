#include "cloud_connector.h"

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "constants.h"
#include "client_info.h"

using namespace std;

CloudConnector::CloudConnector(int port, string host, string client_id) {
  //start thread
  m_thread = thread(&CloudConnector::main_thread, this, port, host, client_id);

  //detach
  m_thread.detach();
}

CloudConnector::~CloudConnector() {
  //empty destructor
}

void CloudConnector::main_thread(int port, string host, string client_id) {
  //init
  int socket_fd = 0;
  char data_buffer[BUFFER_LEN];
  struct sockaddr_in server_address; 

  //clear buffer
  memset(data_buffer, '\0' ,sizeof(data_buffer));
  memset(&server_address, '\0', sizeof(server_address));

  //open socket
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  
  //check socket
  if (socket_fd > 0) {
    //set server info
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(host.c_str());

    //connect to server
    int status = connect(socket_fd, (struct sockaddr *) &server_address, 
      sizeof(server_address));

    //check
    if (status == 0) {
      //get message, cloud only need client id
      string message = ClientInfo(client_id,"","").to_json();

      //send client info
      send(socket_fd, message.c_str(), message.length(), 0);

      //loop
      while (true) {
        //read data from server
        read(socket_fd, data_buffer, BUFFER_LEN);

        cout << "Read data = " << data_buffer << endl;
      }
    }
  }
}

