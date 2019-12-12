/*
 * Dieses Programm liest die Temperatur und Luftfeuchtigkeit mit dem DHT22
 * aus und gibt diese an einem OLED aus.
 * 
 * Johannes Werner
 * 
 * 12/12/2019
 */


#include "DHT.h"      // Einbinden der Arduino DHT Bibliothek
#define DHTPIN 23       // Pin auf dem der DHT verbunden ist (GPIO 23)
#define DHTTYPE DHT22       // DHT Typ
DHT dht(DHTPIN, DHTTYPE);

//Libraries für das OLED Display
#include <Arduino.h>
#include <U8g2lib.h> //Textanzeige
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  // Setup des Displays
  Serial.begin(9600);
  u8g2.begin();
  dht.begin();
}

void loop() {
  delay(2000);        // Sensor kann maximal 0.5Hz. Abfrage alle 3s.
  float h = dht.readHumidity();       //Luftfeuchtigkeit speichern in h
  float t = dht.readTemperature();         //Temperatur speichern in t
  Serial.print(t);        //Ausgabe in der Serial, zum Auslesen am PC
  
  u8g2.clearBuffer();         // clear the internal memory
  
  u8g2.setFont(u8g2_font_5x7_tf); // 6p
  u8g2.drawStr(0,6,"Temperature:");
  u8g2.drawStr(0,40,"Humidity:");
  
  u8g2.setFont(u8g2_font_crox5hb_tf);   // (16p)
  u8g2.setCursor(20,28); //für .print braucht man setCursor
  u8g2.print(t);
  u8g2.setCursor(20,64);
  u8g2.print(h);

  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(90,26,0x2103);
  u8g2.drawGlyph(90,62,0xFF05);
  
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000); 
}
