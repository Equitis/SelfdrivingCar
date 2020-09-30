#include <Arduino.h>
#include <L298N.h>
#include <HCSR04.h>

#define MaxDistance 10
#define FullSpeed 75

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

L298N MotorA(MotorAEnable, MotorAIn1, MotorAIn2);
L298N MotorB(MotorBEnable, MotorBIn1, MotorBIn2);
L298N MotorC(MotorCEnable, MotorCIn1, MotorCIn2);
L298N MotorD(MotorDEnable, MotorDIn1, MotorDIn2);


UltraSonicDistanceSensor DistA(DistA_Trig, DistA_Echo);


void setup()
{
  Serial.begin(9600);
}

double GetDistance(UltraSonicDistanceSensor *sensor)
{
  double distance = sensor->measureDistanceCm();
  if(distance < 0)
  {
    lastValueInvalid = true;
    distance = oldDistance;
  }
  else
  {
    if(lastValueInvalid)
    {
      distance = oldDistance;
    }
    else
    {
      oldDistance = distance;
    }
    lastValueInvalid = false;
  }
}

void SetDirection(double distance)
{
  if(distance > 0 && distance < 10)
  {
    
  }
}

void loop() {
  SetDirection(GetDistance(&DistA));
}

void SetFullSpeed(L298N *motor)
{
  motor->setSpeed(FullSpeed);
}

void TurnLeft(L298N motor)
{

}

void TurnRight(L298N motor)
{

}

void Forward(L298N *motor)
{

}

void Backward(L298N *motor)
{

}

void Stop(L298N *motor)
{

}