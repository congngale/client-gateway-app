#ifndef CLIENT_RESPONSE_H
#define CLIENT_RESPONSE_H

#include <string>

class ClientResponse {
  public:
    ClientResponse(std::string json);
    ClientResponse(int action, std::string id, int status);
    ~ClientResponse();
  
    int action(void);
    int status(void);
    std::string id(void);

    std::string to_json(void);

  private:
    int m_status;
    int m_action;
    std::string m_id;
};

#endif //CLIENT_RESPONSE_H