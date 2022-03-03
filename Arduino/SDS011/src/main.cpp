#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// SDS011 dust sensor example
// -----------------------------
//
// By R. Zschiegner (rz@madavi.de).
// April 2016

#ifdef ESP32
#error ESP32 does not work with SoftSerial, use HardwareSerial example instead
#endif

#include <SDS011.h>

float p10, p25;
int error;

SDS011 my_sds;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  my_sds.begin(2, 3); // RX, TX
  lcd.init();         // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("SDS011 TEST");
  lcd.setCursor(1, 1);
  lcd.print("@azataiot");
  Serial.begin(9600);
  delay(3000);
}

void loop()
{
  error = my_sds.read(&p25, &p10);
  if (!error)
  // lcd.clear();
  {
    Serial.println("P2.5: " + String(p25));
    Serial.println("P10:  " + String(p10));
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("P2.5: " + String(p25));
    lcd.setCursor(1, 1);
    lcd.print("P10:  " + String(p10));
  }
  delay(1000);
}