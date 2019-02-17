#ifndef GATEWAY_CONNECTOR_H
#define GATEWAY_CONNECTOR_H

#include <string>
#include <string.h>

class GatewayConnector {
  public:
    GatewayConnector(int port, std::string host, std::string client_id);
    ~GatewayConnector();

    bool associate(void);
    void send_report(std::string data);
  
  private:
    int m_port;
    std::string m_host;
    std::string m_client_id;


};
#endif //GATEWAY_CONNECTOR_H