#ifndef CLOUD_CONNECTOR_H
#define CLOUD_CONNECTOR_H

#include <string>

class CloudConnector {
  public:
    CloudConnector(int port, std::string host);
    ~CloudConnector();
  
  private:
    int m_port;
    std::string m_host;  
};
#endif //CLOUD_CONNECTOR_H