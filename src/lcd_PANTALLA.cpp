#include "lcd_PANTALLA.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección y tamaño de la pantalla LCD

void setupLCD() {
    lcd.begin(16, 2);
    lcd.print("Iniciando...");
}

void displayData(String voltage, String current, String temperature, String pressure) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("V:" + voltage + " I:" + current);
    lcd.setCursor(0, 1);
    lcd.print("T:" + temperature + " P:" + pressure);
}
