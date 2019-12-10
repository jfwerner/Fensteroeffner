/*
 * Programm zum Auslesen des DHT22 Sensors
 * 5/12/2019
 * Johannes Werner
 */
#include <DHTesp.h>




void setup() {
  Serial.begin(115200);
  
  int dhtPin = 23; //GPIO Port des Pins des DHT22
  dht.setup(dhtPin, DHTesp::DHT22);
  TaskHandle_t tempTaskHandle = NULL;
  DHTesp dht;
}

void loop() {
  TempAndHumidity lastValues = dht.getTempAndHumidity(); //Abfrage der Daten vom Sensor
  delay(3000); //3 sekunden warten: Der Sensor kann mann maximal alle 2s abfragen
  Serial.println("Temperatur ist: " + String(lastValues.temperature,0)); //Temperatur in der Serial ausgeben

}
