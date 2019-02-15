#include <iostream>

#include "constants.h"
#include "gateway_connector.h"

using namespace std;

#define GATEWAY "127.0.0.1"
#define CLOUD "example.cloud.com"

int main(int arg, char *args[]) {
  //init
  bool connected;

  //create connector
  GatewayConnector gateway_connector(PORT, GATEWAY);

  //associate with gateway
  connected = gateway_connector.associate();

  //check 
  if (connected) {
    //TODO implement read sensor data and send report
    //public sample data
    gateway_connector.send_report("250");
  }

  return 0;
}