#ifndef CLOUD_CONNECTOR_H
#define CLOUD_CONNECTOR_H

#include <thread>
#include <string>

#include "bluetooth_service.h"

class CloudConnector {
  public:
    CloudConnector(int port, std::string host, std::string client_id,
      BluetoothService *bluetooth_service);
    ~CloudConnector();
  
  private:
    std::thread m_thread;

    void main_thread(int port, std::string host, std::string client_id,
      BluetoothService *bluetooth_service);
};
#endif //CLOUD_CONNECTOR_H