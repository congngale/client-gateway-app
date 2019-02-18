#include "action.h"

#include <json-c/json.h>

#include "constants.h"

using namespace std;

Action::Action(string json) {
  //parse to json object
  json_object* object = json_tokener_parse(json.c_str());

  //check object
  if(object) {
    //init data
    json_object *data;

    //get sender
    if(json_object_object_get_ex(object, SENDER, &data) &&
      json_object_is_type(data, json_type_string)) {
      //set sender
      m_sender = json_object_get_string(data);
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

Action::~Action() {
  //empty
}

int Action::action() {
  return m_action;
}

string Action::sender() {
  return m_sender;
}