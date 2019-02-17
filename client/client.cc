#include <iostream>

#include <unistd.h>

#include "constants.h"
#include "sensor_handler.h"
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
    //connect to sensor
    SensorHandler sensor_handler(BH1750);

    //loop
    while(true) {
      //read value
      int lux = sensor_handler.read_luminance();

      cout << "Current light: " << lux << endl;

      //send report to gateway
      gateway_connector.send_report(to_string(lux));

      //sleep interval
      usleep(4000000); 
    }
  }

  return 0;
}