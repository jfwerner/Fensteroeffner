/*
 * Johannes Werner
 * 28.11.2019
 * 
 * Steppermotor control program
 * understood and working
 */

#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

//27,26,25,33
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 27, 25, 26, 33);

void setup() {
  // set the speed at 15rpm:
  myStepper.setSpeed(15);
  // initialize the serial port:
  Serial.begin(115200);
}

void loop() {
  int temperature = 23;
  
  while (temperature > 19) {
    // step one revolution  in one direction:
    //Serial.println("clockwise");
    //Anzahl an Schritten (für 1m distanz mit r=3 : 10 240 steps
    myStepper.step(10240);
    //Wartedauer in ms
    delay(3000);
  }
}
