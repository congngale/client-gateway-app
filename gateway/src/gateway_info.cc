#include "gateway_info.h"

#include <json-c/json.h>

#include "constants.h"

using namespace std;

GatewayInfo::GatewayInfo(string id, string ip, string name) {
  //init
  m_id = id;
  m_ip = ip;
  m_name = name;
}

GatewayInfo::~GatewayInfo() {
  //empty destructor
}

string GatewayInfo::to_json() {
  //init json
  string json;

  //create object
  json_object *gateway = json_object_new_object();

  //check
  if (gateway) {
    //append id
    json_object *data = json_object_new_string(m_id.c_str());
    json_object_object_add(gateway, ID, data);

    //append ip
    data = json_object_new_string(m_ip.c_str());
    json_object_object_add(gateway, IP, data);

    //append name
    data = json_object_new_string(m_name.c_str());
    json_object_object_add(gateway, NAME, data);

    //create json string
    json.append(json_object_to_json_string(gateway));

    //clean up
    json_object_put(gateway);
  }

  return json;
}