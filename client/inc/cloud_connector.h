#ifndef CLOUD_CONNECTOR_H
#define CLOUD_CONNECTOR_H

#include <thread>
#include <string>

class CloudConnector {
  public:
    CloudConnector(int port, std::string host, std::string client_id);
    ~CloudConnector();
  
  private:
    std::thread m_thread;

    void main_thread(int port, std::string host, std::string client_id);
};
#endif //CLOUD_CONNECTOR_H