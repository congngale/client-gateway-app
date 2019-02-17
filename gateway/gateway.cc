
#include <fstream>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "mqtt_client.h"
#include "client_manager.h"

using namespace std;

#define INTERVAL 10000 //sleep for 10 miliseconds

int main(int arg, char *args[]) {
  //init
  string gateway_id;

  //read interface
  ifstream net(INTERFACE);

  //check open
  if(net.is_open()) {
    //read mac address
    getline(net, gateway_id);

    //close file
    net.close();
  }

  //check
  if(gateway_id.empty()) {
    cout << "Network interface " << INTERFACE << " is not exist" << endl;
    //exit
    return 0;
  }

  //init broker info
  BrokerInfo broker(17245, "m16.cloudmqtt.com", "Fcz6bH0Q5XIL",
    "abgwsudg");

  //init mqtt client
  MqttClient mqtt_client(broker, gateway_id);

  //start client manager
  ClientManager client_manager(PORT, &mqtt_client);

  //loop
  while(true) {
    //check connection
    mqtt_client.check_connection();

    //sleep interval
    usleep(INTERVAL);    
  }

  return 0;
}