
#include <fstream>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "mqtt_client.h"
#include "http_client.h"
#include "gateway_info.h"
#include "client_manager.h"

using namespace std;

#define INTERVAL 10000 //sleep for 10 miliseconds

int main(int arg, char *args[]) {
  //init
  long status;
  string response;
  string public_ip;
  string gateway_id;
  string gateway_name;
  HttpClient http_client;

  //read interface
  ifstream net(INTERFACE);

  //check open
  if(net.is_open()) {
    //read mac address
    getline(net, gateway_id);

    //close file
    net.close();
  }

  cout << "Gateway mac address =  " << gateway_id << endl;

  //read host name
  ifstream host(HOST_NAME);

  //check
  if (host.is_open()) {
    //read host name
    getline(host, gateway_name);

    //close file
    host.close();
  }

  cout << "Gateway name =  " << gateway_name << endl;

  //get public ip
  status = http_client.get("https://api.ipify.org", &public_ip);

  cout << "Get public ip with status = " << status << ", ip = " 
    << public_ip << endl;

  //check
  if(gateway_id.empty()) {
    //exit
    return 0;
  }

  //init broker info
  BrokerInfo broker(17245, "m16.cloudmqtt.com", "Fcz6bH0Q5XIL",
    "abgwsudg");

  //generate url
  string url = string(CLOUD) + CLOUD_PORT + ADD_GATEWAY;

  //generate gateway
  GatewayInfo gateway(gateway_id, public_ip, gateway_name);

  //register to cloud
  status = http_client.post(url, gateway.to_json(), &response);

  cout << "Add gateway with status = " << status << endl;

  //init mqtt client
  MqttClient mqtt_client(broker, gateway_id);

  //start client manager
  ClientManager client_manager(PORT, &mqtt_client, &http_client);

  //loop
  while(true) {
    //check connection
    mqtt_client.check_connection();

    //sleep interval
    usleep(INTERVAL);    
  }

  return 0;
}