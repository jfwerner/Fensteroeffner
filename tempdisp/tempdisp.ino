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

//--------------------------------------// Setup der dependencies und Initialisierung //--------------------------------------------------


#include "DHT.h"      // Einbinden der Arduino DHT Bibliothek
#define DHTPIN 23       // Pin auf dem der DHT verbunden ist (GPIO 23)
#define DHTTYPE DHT22       // DHT Typ
DHT dht(DHTPIN, DHTTYPE);




#include <WiFi.h> // Telegram Bot und WLAN Libraries
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

char ssid[] = "k3rn3l-p4n1c";     // SSIDhatching boneless machinist brownnose
char password[] = "merrill naval statute dayton"; // Netzwerkschlüssel

#define BOTtoken "821667466:AAFtCtzbe_x4TMjj5ewGQB6EfqG3eppk3H8" 

WiFiClientSecure client; // Initialisierung
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;


//Libraries für das OLED Display
#include <Arduino.h>
#include <U8g2lib.h> // Textanzeige
#include <Wire.h>     // Displaytyp (I2C)

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//Motor initialization
#include <Stepper.h> // Stepper library

const int stepsPerRevolution = 2048;  // Schritte für eine Umdrehung

Stepper myStepper(stepsPerRevolution, 27, 25, 26, 33); // Definierung der Pins (Reihenfolge muss ggf. angepasst werden.)



void setup(void) {
  // Setup des Displays
  Serial.begin(9600);
  u8g2.begin();
  dht.begin();
  // Setup des Motors
  myStepper.setSpeed(15);

  WiFi.mode(WIFI_STA); //WLAN Modus
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { // Von anderem WLAN abmelden
    Serial.print(".");
    delay(500);
  }
}


// Telegram Funktion
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {        //Solange es neue Nachrichten gibt
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";
    //------------ Datenabfrage --------------
    if (text == "/data") {
      bot.sendChatAction(chat_id, "measuring");
      float t = dht.readTemperature();
      float h = dht.readHumidity();
      t = (t-1);
      h = (h-2);
      String welcome = "The current temperature is " + String(t) + "°C,  " + String(273.15 + t) + "K  or " + String(t*1.8 + 32) + "°F.\n" ;
      welcome += "The current measured humidity is " + String(h) + "%.";
      bot.sendMessage(chat_id, welcome);
    }
    //----------- Hilfe -------------
    if (text == "/help") {
      bot.sendChatAction(chat_id, "typing");
      
      String help = "Hi! This bot is connected to a smart window! Don't worry, not Windows 10, so it won't break overnight or crash at random moments ;).";
      help += "\n\nYou can use the following commands:\n";
      
      help += "\n  /data to measure data with the sensor.";
      help += "\n  /status to know if the window is open or closed.";
      bot.sendMessage(chat_id, help);
    }
    //--------- Fensterstatus ---------
    if (text == "/status") {
      bot.sendChatAction(chat_id, "find_location");
      bool windowopen = false;
      if (windowopen = true) {
      String stat = "The window is open.";                //dafür bool funktion bauen
      bot.sendMessage(chat_id, stat);
      }
      if (windowopen = false) {
      String stat = "The window is closed.";
      bot.sendMessage(chat_id, stat);
      }
    }
    //----------- Fehlermeldung --------
    if (text != "/data") {
      bot.sendChatAction(chat_id, "wut???");
      bot.sendMessage(chat_id, String("Sorry m8, dunno what the fuck you sayin. Send me /help for help"));
    }

   //------------ Open --------------------
   if (text == "/open") {
    bot.sendChatAction(chat_id, "typing");
    myStepper.step(10240);
   }
  }
}


//-----------------------// Ausgabe am Display //----------------------------------------------------------------------------------------------------------------
void display(float t, float h) {
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
  //u8g2.drawGlyph(90,26,0x2103);       // U+2103 :  °C 
  u8g2.drawStr(105,26,"K");
  u8g2.drawGlyph(90,62,0x0025);       // U+0025 :  %      (FF05 not working)
  
  u8g2.sendBuffer();          // Befehle an Display senden
  delay(1000);        // 1s warten => 1Hz refresh rate
}

void motor(){
  myStepper.step(10240);//Anzahl an Schritten (für 1m distanz mit r=3 : 10 240 steps
  delay(900000);//Wartedauer in ms (900k = 15min)
  myStepper.step(-10240); // Fenster wieder zu
  delay(900000);
}


void loop() {
  delay(3000);        // Sensor kann maximal 0.5Hz. Abfrage alle 5s.
  float t = dht.readTemperature();         //Temperatur speichern in t
  float h = dht.readHumidity();       //Luftfeuchtigkeit speichern in h
  Serial.print(t);        //Ausgabe in der Serial, zum Auslesen am PC mit dem Serial Monitor
  t = 273.15 + t;
  
  display(t, h);

  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
