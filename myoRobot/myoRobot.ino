// Myo robot sketch
// Bates Tech Club - 2015

#include <MyoController.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#define FIST_PIN 4
#define WAVEIN_PIN 5
#define WAVEOUT_PIN 6
#define FINGERSSPREAD_PIN 7
#define DOUBLETAP_PIN 8

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
MyoController myo = MyoController();

// Add motor objects
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

// Ping setup
int trig = 8; // attach pin 8 to Trig
int echo = 7; //attach pin 7 to Echo
//attach GND to GND and VCC to 5V

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();  // create with the default frequency 1.6KHz
  myo.initMyo();

  // Motor setup
  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(200);
  motor2->setSpeed(200);
  motor3->setSpeed(200);
  motor4->setSpeed(200);
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(FORWARD);
  // turn on motor
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);

  pinMode(echo,INPUT);
  pinMode(trig, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  myo.updatePose();
   
   switch ( myo.getCurrentPose() ) {
    case rest:
      brake();
      delay(100);
      break;
    case fist:
      forward();
      delay(100);
      break;
    case waveIn:
      turnRight();
      delay(100);
      break;
    case waveOut:
      turnLeft();
      delay(100);
      break;
    case fingersSpread:
      back();
      delay(100);
      break;
    case doubleTap:
    
      break;
   } 
}

////////// Motion functions ///////////

void brake() {
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
  
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  motor3->setSpeed(0);
  motor4->setSpeed(0);
}

void forward() {
  // Robot moves forward
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(FORWARD);
  
  motor1->setSpeed(100);
  motor2->setSpeed(100);
  motor3->setSpeed(100);
  motor4->setSpeed(100);
}

void back() {
  // Robot moves back
  motor1->run(BACKWARD);
  motor2->run(BACKWARD);
  motor3->run(BACKWARD);
  motor4->run(BACKWARD);
  // Set robot speed here.
  motor1->setSpeed(100);
  motor2->setSpeed(100);
  motor3->setSpeed(100);
  motor4->setSpeed(100);
}

void turnLeft() {
  // Rotate 2 wheels forward, other 2 backwards
  motor1->run(BACKWARD);
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(BACKWARD);
  // Set robot speed here.
  motor1->setSpeed(200);
  motor2->setSpeed(200);
  motor3->setSpeed(200);
  motor4->setSpeed(200);
}

void turnRight() {
  // Rotate 2 wheels forward, other 2 backwards
  motor1->run(FORWARD);
  motor2->run(BACKWARD);
  motor3->run(BACKWARD);
  motor4->run(FORWARD);
  // Set robot speed here.
  motor1->setSpeed(200);
  motor2->setSpeed(200);
  motor3->setSpeed(200);
  motor4->setSpeed(200);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}
