#include "client_info.h"

#include <json-c/json.h>

#include "constants.h"

using namespace std;

ClientInfo::ClientInfo(string id, string ip, string name, int threshold) {
  //init
  m_id = id;
  m_ip = ip;
  m_name = name;
  m_threshold = threshold;
}

ClientInfo::~ClientInfo() {
  //empty destructor
}

string ClientInfo::to_json() {
  //init json
  string json;

  //create object
  json_object *client = json_object_new_object();

  //check
  if (client) {
    //append id
    json_object *data = json_object_new_string(m_id.c_str());
    json_object_object_add(client, ID, data);

    //append ip
    data = json_object_new_string(m_ip.c_str());
    json_object_object_add(client, IP, data);

    //append name
    data = json_object_new_string(m_name.c_str());
    json_object_object_add(client, NAME, data);

    //append threshold
    data = json_object_new_int(m_threshold);
    json_object_object_add(client, THRESHOLD, data);

    //create json string
    json.append(json_object_to_json_string(client));

    //clean up
    json_object_put(client);
  }

  return json;
}