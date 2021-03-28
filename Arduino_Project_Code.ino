#include <Servo.h>

//Define the pins for which the joystick and servo wires are connected
const int ledPin = 13;
const int xPin = A0; // define X-axis pin
const int yPin = A1; // define Y-axis pin
const int switchPin = 2;
const int servoxPin = 10;
const int servoyPin = 11; 

int xValue;
int yValue;
int X_pos = 10; // set home position for servos
int Y_pos = 30; // set home position for servos

volatile int switchState = 0;
 
Servo servox;
Servo servoy;

void setup() 
{
  pinMode (xPin, INPUT) ;                     
  pinMode (yPin, INPUT) ;
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  servox.attach(servoxPin); // attaching servo X
  servoy.attach(servoyPin); // attaching servo Y
  servox.write(X_pos); // update X_pos with home position as startup
  servoy.write(Y_pos); // update Y_pos with home position as startup
  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, CHANGE);
}

void loop() 
{
  xValue = analogRead(xPin);  
  yValue = analogRead(yPin);
// For X-Axis Servo
  if (xValue < 300)
  {
    if (X_pos < -130) 
    {
      // Do Nothing 
    } 
    else
    {
      X_pos = X_pos - 5;
      servox.write(X_pos);
      delay(100); 
    } 
  } 
  
  if (xValue > 700)
  {
    if (X_pos > 30)
    {
      // Do Nothing  
    }
    else
    {
      X_pos = X_pos + 5;
      servox.write(X_pos);
      delay(100);
    }
  }
// For Y-Axis Servo
if (yValue < 300)
  {
    if (Y_pos < -30) 
    {
      // Do Nothing 
    } 
    else
    {
      Y_pos = Y_pos - 5;
      servoy.write(Y_pos);
      delay(100); 
    } 
  } 
  
  if (yValue > 700)
  {
    if (Y_pos > 50)
    {
      // Do Nothing  
    }
    else
    {
      Y_pos = Y_pos + 5;
      servoy.write(Y_pos);
      delay(100);
    }
  }
}

void switchISR()
{
  switchState = digitalRead(switchPin);
  digitalWrite(ledPin, switchState);
}
