#include "message.h"

#include "constants.h"

using namespace std;

Message::Message(string client_id, string data) {
  //init
  m_data = data;
  m_client_id = client_id;
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
    json_object_object_add(message, CLIENT_ID, json_object_new_string(
      m_client_id.c_str()));

    //append data
    json_object_object_add(message, DATA, get_value_object(m_data));

    //create json string
    json.append(json_object_to_json_string(message));

    //clean up
    json_object_put(message);
  }

  return json;
}

json_object* Message::get_value_object(string value) {
  //init object
  json_object* attribute;

  //check value
  if(value == TRUE_VALUE || value == FALSE_VALUE) {
    //boolean attribute
    attribute = json_object_new_boolean(value == TRUE_VALUE);
  } else {
    try {
      //init index
      size_t index;

      //integer or long attribute
      attribute = json_object_new_int64(stol(value, &index));

      //check index position
      if (index < value.length()) {
        //string attribute not long/integer
        attribute = json_object_new_string(value.c_str());
      }
    } catch (exception &e) {
      //exception means string attribute
      attribute = json_object_new_string(value.c_str());
    }
  }

  return attribute;
}