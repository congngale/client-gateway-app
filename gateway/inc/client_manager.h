#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <set>
#include <thread>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "mqtt_client.h"

#define BUFFER_LEN 4096

class ClientManager {
  public:
    ClientManager(int port, MqttClient *mqtt_client, std::string gateway_id);
    ~ClientManager();
  
  private:
    std::thread m_thread;

    void main_thread(int port, MqttClient *mqtt_client,
      std::string gateway_id);
    void handle_request(int socket_fd, std::string data,
      MqttClient *mqtt_client, struct sockaddr_in *client_address, 
      socklen_t client_address_len, std::set<std::string> *clients,
      std::string gateway_id);
};
#endif //CLIENT_MANAGER_H