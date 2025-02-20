#include <Arduino.h>
#include <WiFi.h>
#include "ina219_VOLT.h"
#include "lm35_TEMP.h"
#include "mh_flyingfish_RPM.h"
#include "lcd_PANTALLA.h"

const char *ssid = "ESP32_G2";
const char *password = "Grupo_02";
WiFiServer server(5000);
//WiFiServer server(12345);

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    Serial.println("WiFi AP creado. IP: " + WiFi.softAPIP().toString());
    
    setupINA219();
    setupMHFlyingFish();
    setupLCD();
    
    server.begin();
    Serial.println("Servidor iniciado.");
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("Cliente conectado.");
        while (client.connected()) {
            // Leer los datos de los sensores
            String voltage = readINA219Data();
            String current = voltage.substring(voltage.indexOf(",") + 1);
            voltage = voltage.substring(0, voltage.indexOf(","));
            String temperature = String(readLM35Data());
            String rpm = String(readMHFlyingFishData());
            
            displayData(voltage, current, temperature, rpm);
            String data = voltage + "," + current + "," + temperature + "," + rpm + "\n";
            client.print(data);
            Serial.println("Datos enviados: " + data);
            delay(3000);
        }
        client.stop();
    }
}