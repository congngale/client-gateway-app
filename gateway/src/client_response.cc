#include "client_response.h"

#include <json-c/json.h>

#include "constants.h"

using namespace std;

ClientResponse::ClientResponse(string json) {
  //parse to json object
  json_object* object = json_tokener_parse(json.c_str());

  //check object
  if(object) {
    //init data
    json_object *data;

    //get id
    if(json_object_object_get_ex(object, ID, &data) &&
      json_object_is_type(data, json_type_string)) {
      //set id
      m_id = json_object_get_string(data);
    }

    //get status
    if(json_object_object_get_ex(object, STATUS, &data) &&
      json_object_is_type(data, json_type_int)) {
      //set status
      m_status = json_object_get_int(data);
    }

    //get action
    if(json_object_object_get_ex(object, ACTION, &data) &&
      json_object_is_type(data, json_type_int)) {
      //set action
      m_action = json_object_get_int(data);
    }

    //clean up
    json_object_put(object);
  }
}

ClientResponse::ClientResponse(int action, string id, int status) {
  //init
  m_id = id;
  m_status = status;
  m_action = action;
}

ClientResponse::~ClientResponse() {
  //empty destructor
}

string ClientResponse::id() {
  return m_id;
}

int ClientResponse::status() {
  return m_status;
}

int ClientResponse::action() {
  return m_action;
}

string ClientResponse::to_json() {
  //init json
  string json;

  //create object
  json_object *response = json_object_new_object();

  //check
  if (response) {
    //append id
    json_object *data = json_object_new_string(m_id.c_str());
    json_object_object_add(response, ID, data);

    //append data
    data = json_object_new_int(m_status);
    json_object_object_add(response, STATUS, data);

    //append status
    data = json_object_new_int(m_action);
    json_object_object_add(response, DATA, data);

    //create json string
    json.append(json_object_to_json_string(response));

    //clean up
    json_object_put(response);
  }

  return json;
}