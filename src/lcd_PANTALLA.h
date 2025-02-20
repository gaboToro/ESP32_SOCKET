#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void setupLCD();
void displayData(String voltage, String current, String temperature, String rpm);

#endif
