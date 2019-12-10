/*
 * Dieses Programm liest die Temperatur und Luftfeuchtigkeit mit dem DHT22
 * aus und gibt diese an einem OLED aus.
 */


#include "DHT.h"
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  Serial.begin(9600);
  
  u8g2.begin();
  dht.begin();
}

void loop() {
  delay(3000); // 3 s warten zwischen Messungen, der Sensor kann max. 0,5Hz
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_courB10_tf); // choose a suitable font
  //u8g2.drawStr(0,10,"Hello World!");  // write something to the internal memory
  u8g2.drawStr(0,20,"Temperature");
  u8g2.setFont(u8g2_font_courB24_tf);
  u8g2.setCursor(0,50); //für .print braucht man setCursor
  u8g2.drawStr(100,50,"°C");
  u8g2.print(t);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000); 
}
