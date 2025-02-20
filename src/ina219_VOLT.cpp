#include "ina219_VOLT.h"
#include <Wire.h>

Adafruit_INA219 ina219;

void setupINA219() {
    if (!ina219.begin()) {
        Serial.println("Error al iniciar INA219");
        while (1);
    }
}

String readINA219Data() {
    float voltage = ina219.getBusVoltage_V();
    float current = ina219.getCurrent_mA();
    return String(voltage) + "," + String(current);
}