
#include <fstream>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include "mqtt_client.h"
#include "client_manager.h"

using namespace std;

#define PORT 2019
#define INTERVAL 10000 //sleep for 10 miliseconds
#define INTERFACE "/sys/class/net/enp0s3/address"

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

  //init broker info
  BrokerInfo broker(17245, "m16.cloudmqtt.com", "Fcz6bH0Q5XIL",
    "abgwsudg");

  //init mqtt client
  MqttClient mqtt_client(broker, gateway_id);

  //start client manager
  ClientManager client_manager(PORT, &mqtt_client, gateway_id);

  //loop
  while(true) {
    //check connection
    mqtt_client.check_connection();

    //sleep interval
    usleep(INTERVAL);    
  }

  return 0;
}