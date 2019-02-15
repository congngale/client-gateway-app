#include "client_request.h"

#include <json-c/json.h>

#include "constants.h"

using namespace std;

ClientRequest::ClientRequest(string json) {
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

    //get data
    if(json_object_object_get_ex(object, DATA, &data) &&
      json_object_is_type(data, json_type_string)) {
      //set data
      m_data = json_object_get_string(data);
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

ClientRequest::ClientRequest(int action, string id, string data) {
  //init
  m_id = id;
  m_data = data;
  m_action = action;
}

ClientRequest::~ClientRequest() {
  //empty destructor
}

string ClientRequest::id() {
  return m_id;
}

string ClientRequest::data() {
  return m_data;
}

int ClientRequest::action() {
  return m_action;
}

string ClientRequest::to_json() {
  //init json
  string json;

  //create object
  json_object *request = json_object_new_object();

  //check
  if (request) {
    //append id
    json_object *data = json_object_new_string(m_id.c_str());
    json_object_object_add(request, ID, data);

    //append data
    data = json_object_new_string(m_data.c_str());
    json_object_object_add(request, DATA, data);

    //append action
    data = json_object_new_int(m_action);
    json_object_object_add(request, ACTION, data);

    //create json string
    json.append(json_object_to_json_string(request));

    //clean up
    json_object_put(request);
  }

  return json;
}