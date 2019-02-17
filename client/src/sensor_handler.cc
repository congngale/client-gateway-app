#include "sensor_handler.h"

SensorHandler::SensorHandler(int sensor_type) {
  //connect to sensor
  m_sensor_fd = wiringPiI2CSetup(sensor_type);
}

SensorHandler::~SensorHandler() {
  //empty destructor
}

int SensorHandler::read_luminance() {
  // One-time measurement at 0.5 lx resolution. 
  // Measurement Time is typically 120ms. 
  //It is automatically set to Power Down mode after measurement.
  wiringPiI2CWrite(handle, 0x21);
  
  sleep(1);

  //read data
  int word = wiringPiI2CReadReg16(handle, 0x00);

  return ((word & 0xff00)>>8) | ((word & 0x00ff)<<8);
}