#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_INA219.h>

const char *ssid = "ESP32_G2";
const char *password = "Grupo_02";
WiFiServer server(12345);
Adafruit_INA219 ina219;

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    Serial.println("WiFi AP creado. IP: " + WiFi.softAPIP().toString());

    if (!ina219.begin()) {
        Serial.println("Error al iniciar INA219");
        while (1);
    }

    server.begin();
    Serial.println("Servidor de sockets iniciado.");
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("Cliente conectado.");
        while (client.connected()) {
            float voltage = ina219.getBusVoltage_V();
            //float voltage = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000);
            float current = ina219.getCurrent_mA();

            String data = String(voltage) + "," + String(current) + "\n";
            client.print(data);
            Serial.println("Datos enviados: " + data);

            delay(3000);
        }
        client.stop();
        Serial.println("Cliente desconectado.");
    }
}
