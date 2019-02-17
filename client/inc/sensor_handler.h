#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <stdio.h>
#include <wiringPiI2C.h>

#define BH1750 0x23

class SensorHandler {
  public:
    SensorHandler(int sensor_type);
    ~SensorHandler();
    
    int read_luminance(void);

  private:
    int m_sensor_fd;
};

#endif //SENSOR_HANDLER_H