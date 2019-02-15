#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <json-c/json.h>

class Message {
  public:
    Message(std::string client_id, std::string data);
    ~Message();

    std::string to_json(void);
  
  private:
    std::string m_data;
    std::string m_client_id;

    json_object* get_value_object(std::string value);
};
#endif //MESSAGE_H