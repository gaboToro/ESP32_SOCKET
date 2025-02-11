#include <Arduino.h>
#include <WiFi.h>
#include "ina219_VOLT.h"
#include "lm35_TEMP.h"
#include "mps20n0040d_PRES.h"
#include "lcd_PANTALLA.h"

const char *ssid = "ESP32_G2";
const char *password = "Grupo_02";
WiFiServer server(12345);

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    Serial.println("WiFi AP creado. IP: " + WiFi.softAPIP().toString());
    
    setupINA219();
    setupMPS20N0040D();
    setupLCD();
    
    server.begin();
    Serial.println("Servidor de sockets iniciado.");
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
            String pressure = String(readMPS20N0040DData());
            
            // Mostrar en LCD
            displayData(voltage, current, temperature, pressure);
            
            // Enviar datos al cliente
            String data = voltage + "," + current + "," + temperature + "," + pressure + "\n";
            client.print(data);
            Serial.println("Datos enviados: " + data);

            delay(3000);  // Espera 3 segundos antes de enviar de nuevo
        }
        client.stop();
        Serial.println("Cliente desconectado.");
    }
}
