#include "gateway_connector.h"

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "status.h"
#include "command.h"
#include "constants.h"
#include "client_request.h"
#include "client_response.h"

using namespace std;

GatewayConnector::GatewayConnector(int port, string host) {
  //init
  m_port = port;
  m_host = host;

  //read interface
  ifstream net(INTERFACE);

  //check open
  if(net.is_open()) {
    //read mac address
    getline(net, m_client_id);

    //close file
    net.close();
  }
}

GatewayConnector::~GatewayConnector() {
  //empty destructor
}

bool GatewayConnector::associate() {
  //init
  bool ret = false;
  int socket_fd = 0;
  char data_buffer[BUFFER_LEN];
  struct sockaddr_in server_address;
  socklen_t server_address_len = sizeof(server_address);

  //clear buffer
  memset(data_buffer, '\0' ,sizeof(data_buffer));
  memset(&server_address, '\0', sizeof(server_address));

  //create socket
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

  //check socket
  if (socket_fd > 0) {
    //set server info
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(m_port);
    server_address.sin_addr.s_addr = inet_addr(m_host.c_str());

    //generate associate message
    string message = ClientRequest(Command::ADD, m_client_id, "").to_json();

    //send report
    sendto(socket_fd, message.c_str(), message.length(), MSG_CONFIRM, 
      (const struct sockaddr*) &server_address, sizeof(server_address));

    //receive data from gateway
    int data_len = recvfrom(socket_fd, data_buffer, BUFFER_LEN,
      MSG_WAITALL, (struct sockaddr*) &server_address, 
      &server_address_len);

    //check data
    if (data_len > 0) {
      //convert to model
      ClientResponse response(string(data_buffer, data_len));

      //check status
      switch (response.status()) {
        case Status::NEW: {
          ret = true;
          cout << "Success to associate with gateway." << endl;
          break;
        }

        case Status::EXISTED: {
          ret = true;
          cout << "Already associate with gateway." << endl;
          break;
        }

        case Status::INVALID: {
          cout << "Failed to associate with gateway." << endl;
          break;
        }
      }
    }

    //close socket
    close(socket_fd);
  }

  return ret;
}

void GatewayConnector::send_report(string data) {
  //init
  int socket_fd = 0;
  char data_buffer[BUFFER_LEN];
  struct sockaddr_in server_address;

  //clear buffer
  memset(data_buffer, '\0' ,sizeof(data_buffer));
  memset(&server_address, '\0', sizeof(server_address));

  //create socket
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

  //check socket
  if (socket_fd > 0) {
    //set server info
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(m_port);
    server_address.sin_addr.s_addr = inet_addr(m_host.c_str());

    //get message
    string message = ClientRequest(Command::REPORT, m_client_id, data).to_json();

    //send report
    sendto(socket_fd, message.c_str(), message.length(), MSG_CONFIRM, 
      (const struct sockaddr*) &server_address, sizeof(server_address));

    //close socket
    close(socket_fd);
  }
}