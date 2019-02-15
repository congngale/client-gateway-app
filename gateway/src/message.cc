#include "message.h"

#include <json-c/json.h>

#include "constants.h"

using namespace std;

Message::Message(string gateway_id, string client_id, string data) {
  //init
  m_data = data;
  m_client_id = client_id;
  m_gateway_id = gateway_id;
}

Message::~Message() {
  //empty destructor
}

string Message::to_json() {
  //init json
  string json;

  //create object
  json_object *message = json_object_new_object();

  //check
  if (message) {
    //append id
    json_object *data = json_object_new_string(m_data.c_str());
    json_object_object_add(message, DATA, data);

    //append data
    data = json_object_new_string(m_client_id.c_str());
    json_object_object_add(message, CLIENT_ID, data);

    //append action
    data = json_object_new_string(m_gateway_id.c_str());
    json_object_object_add(message, GATEWAY_ID, data);

    //create json string
    json.append(json_object_to_json_string(message));

    //clean up
    json_object_put(message);
  }

  return json;
}