#ifndef GATEWAY_INFO_H
#define GATEWAY_INFO_H

#include <string>

class GatewayInfo {
  public:
    GatewayInfo(std::string id, std::string ip, std::string name);
    ~GatewayInfo();

    std::string to_json(void);
  
  private:
    std::string m_id;
    std::string m_ip;
    std::string m_name;
};
#endif //GATEWAY_INFO_H