#include <iostream>

#include <fstream>
#include <unistd.h>

#include "constants.h"
#include "sensor_handler.h"
#include "cloud_connector.h"
#include "bluetooth_service.h"
#include "gateway_connector.h"

using namespace std;

#define LED_MAC "F8:1D:78:60:3D:96"

int main(int arg, char *args[]) {
  //init
  bool connected;
  string client_id;

  //read interface
  ifstream net(INTERFACE);

  //check open
  if(net.is_open()) {
    //read mac address
    getline(net, client_id);

    //close file
    net.close();
  }

  //create bluetooth service
  BluetoothService bluetooth_service(LED_MAC);

  //create gateway connector
  GatewayConnector gateway_connector(PORT, GATEWAY, client_id);

  //create cloud connector
  CloudConnector cloud_connector(PORT, CLOUD, client_id, &bluetooth_service);

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
