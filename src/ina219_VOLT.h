#ifndef INA219_SENSOR_H
#define INA219_SENSOR_H

#include <Adafruit_INA219.h>

extern Adafruit_INA219 ina219;

void setupINA219();
String readINA219Data();

#endif
