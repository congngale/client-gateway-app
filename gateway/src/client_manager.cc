#include "client_manager.h"

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "status.h"
#include "command.h"
#include "message.h"
#include "constants.h"
#include "client_request.h"
#include "client_response.h"

using namespace std;

ClientManager::ClientManager(int port, MqttClient *mqtt_client) {
  //start thread
  m_thread = thread(&ClientManager::main_thread, this, port, mqtt_client);

  //detach
  m_thread.detach();
}

ClientManager::~ClientManager() {
  //empty destructor
}

void ClientManager::main_thread(int port, MqttClient *mqtt_client) {
  //init
  int socket_fd = 0;
  char data_buffer[BUFFER_LEN];
  struct sockaddr_in server_address;

  //init client list
  set<string> clients;

  // creating socket
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

  //clear ip struct
  memset(data_buffer, '\0' ,sizeof(data_buffer));
  memset(&server_address, '\0', sizeof(server_address));

  //set server info
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  //binding socket into port and ip address
  bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address));

  cout << "Started server with port " << port <<endl;

  //loop
  while(true) {
    //init client structure
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    //clean up memory
    memset(&client_address, '\0', sizeof(client_address));

    //receive data from client
    int data_len = recvfrom(socket_fd, data_buffer, BUFFER_LEN, MSG_WAITALL,
      (struct sockaddr*) &client_address, &client_address_len);

    //check
    if (data_len > 0) {
      //handle request
      handle_request(socket_fd, string(data_buffer, data_len), mqtt_client,
        &client_address, client_address_len, &clients);
    }
  }
}

void ClientManager::handle_request(int socket_fd, string data,
  MqttClient *mqtt_client, struct sockaddr_in *client_address, socklen_t 
  client_address_len, set<string> *clients) {
  //get client ip
  char client_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(client_address->sin_addr), client_ip, INET_ADDRSTRLEN);

  cout << "Client request with ip = " << client_ip << endl;

  //convert into model
  ClientRequest request(data);

  //check action
  switch (request.action()) {
    case Command::ADD: {
      //init response
      string response;

      //check empty
      if (!request.id().empty()) {
        //insert client
        auto it = clients->insert(request.id());
        

        //check result
        if (it.second) {
          cout << "Add new client with id = " << request.id() << endl;
          //set success response
          response = ClientResponse(Command::ADD, request.id(),
            Status::NEW).to_json();
        } else {
          //set fail response
          response = ClientResponse(Command::ADD, request.id(),
            Status::EXISTED).to_json();
        }
      } else {
        //set wrong status
        response = ClientResponse(Command::ADD, request.id(),
            Status::INVALID).to_json();
      }

      //send response
      sendto(socket_fd, response.c_str(), response.length(), MSG_CONFIRM,
        (const struct sockaddr*) client_address, client_address_len);
      break;
    }

    case Command::REPORT: {
      //search client
      auto it = clients->find(request.id());
      
      //check client exist
      if (it != clients->end()) {
        cout << "Publish data = " << request.data() << endl;

        //build message
        Message message(request.id(), request.data());

        //public data to cloud mqtt with QoS = 1
        mqtt_client->publish_message(message.to_json(), 1);
      }
      break;
    }
  }
}