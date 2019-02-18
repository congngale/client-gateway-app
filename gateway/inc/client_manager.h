#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <set>
#include <thread>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "http_client.h"
#include "mqtt_client.h"

class ClientManager {
  public:
    ClientManager(int port, MqttClient *mqtt_client, HttpClient *http_client);
    ~ClientManager();
  
  private:
    std::thread m_thread;

    void main_thread(int port, MqttClient *mqtt_client,
      HttpClient *http_client);
    void handle_request(int socket_fd, std::string data,
      MqttClient *mqtt_client, HttpClient *http_client, 
      struct sockaddr_in *client_address, socklen_t client_address_len, 
      std::set<std::string> *clients);
};
#endif //CLIENT_MANAGER_H