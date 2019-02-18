#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <string>

class ClientInfo {
  public:
    ClientInfo(std::string id, std::string ip, std::string name,
      int threshold);
    ~ClientInfo();

    std::string to_json(void);
  
  private:
    int m_threshold;
    std::string m_id;
    std::string m_ip;
    std::string m_name;
};
#endif //CLIENT_INFO_H