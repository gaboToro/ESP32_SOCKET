#include <Arduino.h>
#include "lm35_TEMP.h"

#define LM35_PIN 34  // Define el pin donde está conectado el LM35 (GPIO34 por ejemplo)

float readLM35Data() {
    // Configura el pin como entrada analógica
    int rawValue = analogRead(LM35_PIN);  // Lee el valor analógico
    // Convierte el valor leído en una temperatura en °C, considerando que el LM35 tiene una salida de 10mV/°C
    float temperature = (rawValue / 4095.0) * 100.0;  // Conversión de valor a °C
    return temperature;
}