#ifndef CLIENT_REQUEST_H
#define CLIENT_REQUEST_H

#include <string>

class ClientRequest {
  public:
    ClientRequest(std::string json);
    ClientRequest(int action, std::string id, std::string data);
    ~ClientRequest();
  
    int action(void);
    std::string id(void);
    std::string data(void);

    std::string to_json(void);

  private:
    int m_action = 0;
    std::string m_id;
    std::string m_data;
};

#endif //CLIENT_REQUEST_H