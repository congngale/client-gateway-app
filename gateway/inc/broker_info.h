#ifndef BROKER_INFO_H
#define BROKER_INFO_H

#include <string>

class BrokerInfo {
  public:
    BrokerInfo();
    BrokerInfo(int port, std::string host, std::string password,
      std::string username);
    ~BrokerInfo();

    int port(void);
    std::string host(void);
    std::string password(void);
    std::string username(void);
    std::string to_string(void);
  
  private:
    int m_port;
    std::string m_host;
    std::string m_password;
    std::string m_username;
};

#endif //BROKER_INFO_H