/*  Programm: Fensteröffner
 *  
 *  Autor: Johannes Werner
 *  
 *  Zweck: Auslesen der Temperatur und Luftfeuchtigkeit mithilfe des DHT22. Anzeige in human readable format in °C und %.
 *  
 *  Nutzen der Werte zur Steuerung eines 28BY ... Schrittmotors mit einem xxxxx Motortreibers um ein Fenster zu öffnen und zu schließen.
 *  
 *  Changelog auf github.com
 */

--------------------------------------// Setup der dependencies und Initialisierung //--------------------------------------------------


#include "DHT.h"      // Einbinden der Arduino DHT Bibliothek
#define DHTPIN 23       // Pin auf dem der DHT verbunden ist (GPIO 23)
#define DHTTYPE DHT22       // DHT Typ
DHT dht(DHTPIN, DHTTYPE);

//Libraries für das OLED Display
#include <Arduino.h>
#include <U8g2lib.h> // Textanzeige
#include <Wire.h>     // Displaytyp (I2C)

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  // Setup des Displays
  Serial.begin(9600);
  u8g2.begin();
  dht.begin();
}

void loop() {
  delay(2000);        // Sensor kann maximal 0.5Hz. Abfrage alle 2s.
  float h = dht.readHumidity();       //Luftfeuchtigkeit speichern in h
  float t = dht.readTemperature();         //Temperatur speichern in t
  Serial.print(t);        //Ausgabe in der Serial, zum Auslesen am PC mit dem Serial Monitor

-----------------------// Ausgabe am Display //----------------------------------------------------------------------------------------------------------------


  u8g2.clearBuffer();         // Display löschen
  
  u8g2.setFont(u8g2_font_5x7_tf);         // 6 pixel groß
  u8g2.drawStr(0,6,"Temperature:");       // u8g2.drawStr(x,y,"text");
  u8g2.drawStr(0,40,"Humidity:");
  
  u8g2.setFont(u8g2_font_crox5hb_tf);       // 18 pixel groß
  u8g2.setCursor(20,28);        //für .print braucht man setCursor, nicht die Syntax (x,y,[text])
  u8g2.print(t);
  u8g2.setCursor(20,64);
  u8g2.print(h);

  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(90,26,0x2103);       // U+2103 :  °C
  u8g2.drawGlyph(90,62,0xFF05);       // U+FF05 :  %      NOT WORKING
  
  u8g2.sendBuffer();          // Befehle an Display senden
  delay(1000);        // 1s warten => 1Hz refresh rate
}
