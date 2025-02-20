#include "mh_flyingfish_RPM.h"

#define SENSOR_PIN 15  // GPIO 15
volatile int contador = 0;
volatile unsigned long ultimoTiempo = 0;
const unsigned long tiempoRebote = 5;  // 5 ms antirrebote

void IRAM_ATTR contarPulsos() {
    unsigned long ahora = millis();
    if (ahora - ultimoTiempo > tiempoRebote) {
        contador++;
        ultimoTiempo = ahora;
    }
}

void setupMHFlyingFish() {
    pinMode(SENSOR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), contarPulsos, RISING);
}

float readMHFlyingFishData() {
    static unsigned long tiempoAnterior = millis();
    unsigned long tiempoActual = millis();
    float rpm = 0.0;

    if (tiempoActual - tiempoAnterior >= 1000) {
        rpm = contador * 60.0;
        contador = 0;
        tiempoAnterior = tiempoActual;
    }
    return rpm;
}