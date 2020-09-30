#include <Arduino.h>
#include <L298N.h>
#include <HCSR04.h>

#define MaxDistance 10
#define FullSpeed 75
#define DefaultDelay 100

#define MotorAIn1 32
#define MotorAIn2 34
#define MotorBIn1 30
#define MotorBIn2 28

#define MotorCIn1 38
#define MotorCIn2 40
#define MotorDIn1 42
#define MotorDIn2 44

#define MotorAEnable 2
#define MotorBEnable 3
#define MotorCEnable 5
#define MotorDEnable 6

#define DistA_Trig 25
#define DistA_Echo 23

bool obstacleLeft = false;
bool obstacleFront = false;
bool obstacleRight = false;
bool lastValueInvalid = false;
double oldDistance = 0;
int counter = 0;

L298N MotorA(MotorAEnable, MotorAIn1, MotorAIn2);
L298N MotorB(MotorBEnable, MotorBIn1, MotorBIn2);
L298N MotorC(MotorCEnable, MotorCIn1, MotorCIn2);
L298N MotorD(MotorDEnable, MotorDIn1, MotorDIn2);


UltraSonicDistanceSensor DistA(DistA_Trig, DistA_Echo);


void setup()
{
  Serial.begin(9600);
}

bool GetDistance(UltraSonicDistanceSensor *sensor)
{
  //Hole Werte vom Sensor
  double distance = sensor->measureDistanceCm();
  //Prüfe auf ungültige Werte
  if(distance < 0)
  {
    lastValueInvalid = true;
    distance = oldDistance;
  }
  else
  {
    if(lastValueInvalid)
    {
      //Wenn der letzte Wert ungültig war setze den letzten gültigen Wert
      distance = oldDistance;
    }
    else
    {
      oldDistance = distance;
    }
    lastValueInvalid = false;
  }
  // gebe den letzten gültigen Wert zurück
  return distance <= MaxDistance;
}

void Stop()
{
  MotorA.setSpeed(0);
  MotorA.stop();
  MotorB.setSpeed(0);
  MotorB.stop();
  MotorC.setSpeed(0);
  MotorC.stop();
  MotorD.setSpeed(0);
  MotorD.stop();
}

void SetFullSpeed()
{
  MotorA.setSpeed(FullSpeed);
  MotorB.setSpeed(FullSpeed);
  MotorC.setSpeed(FullSpeed);
  MotorD.setSpeed(FullSpeed);
}

void TurnLeft()
{
  Stop();
  MotorA.backward();
  MotorB.backward();
  MotorC.forward();
  MotorD.forward();
  SetFullSpeed();
  delay(DefaultDelay);
}

void TurnRight()
{
  Stop();
  MotorA.forward();
  MotorB.forward();
  MotorC.backward();
  MotorD.backward();
  SetFullSpeed();
  delay(DefaultDelay);
}

void Forward()
{
  MotorA.forward();
  MotorB.forward();
  MotorC.forward();
  MotorD.forward();
}

void Backward()
{
  MotorA.backward();
  MotorB.backward();
  MotorC.backward();
  MotorD.backward();
}

void loop() {
  bool obstacle = true;
  do
  {
    obstacle = GetDistance(&DistA);
    if(obstacle)
    {
        Stop();
        if(counter < 10)
        {
          TurnLeft();
        }
        else if (counter >= 10 && counter < 30)
        {
          TurnRight();
        }
        else if (counter >= 30 && counter < 40)
        {
          TurnLeft();
        }
        else
        {
          Backward();
          delay(500);
          counter = 0;
        }
    }
    ++counter;
    delay(100);
  } while (!obstacle);

  Forward();

}