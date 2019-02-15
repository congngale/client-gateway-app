#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message {
  public:
    Message(std::string gateway_id, std::string client_id, 
      std::string data);
    ~Message();

    std::string to_json(void);
  
  private:
    std::string m_data;
    std::string m_client_id;  
    std::string m_gateway_id;
};
#endif //MESSAGE_H