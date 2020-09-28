#include <Arduino.h>
#include "Ultrasonic.h"
#include "L298N.h"

#define FullSpeed 75

#define MotorAIn1 32
#define MotorAIn2 34
#define MotorBIn1 30
#define MotorBIn2 28

#define MotorCIn1 38
#define MotorCIn2 40
#define MotorDIn1 44
#define MotorDIn2 42

#define MotorAEnable 2
#define MotorBEnable 3
#define MotorCEnable 5
#define MotorDEnable 6

L298N MotorA(MotorAEnable, MotorAIn1, MotorAIn2);
L298N MotorB(MotorBEnable, MotorBIn1, MotorBIn2);
L298N MotorC(MotorCEnable, MotorCIn1, MotorCIn2);
L298N MotorD(MotorDEnable, MotorDIn1, MotorDIn2);

void setup() {
  Serial.begin(9600); 
  MotorA.setSpeed(FullSpeed);
  MotorB.setSpeed(FullSpeed);
  MotorC.setSpeed(FullSpeed);
  MotorD.setSpeed(FullSpeed);
}

void loop() {
  MotorA.forward();
  MotorB.forward();
  MotorC.forward();
  MotorD.forward();
  Serial.write("Forward\n");
  delay(500);
 }