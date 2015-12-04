
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

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
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

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
  
  long duration, inches, cm;

  // Get ping data
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  Serial.println(inches);

  forward();

  if (inches < 5) {
    brake();
    turnAround();
    delay(3000);
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

void turnAround() {
  // Rotate 2 wheels forward, other 2 backwards
  motor1->run(BACKWARD);
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(BACKWARD);
  // Set robot speed here.
  motor1->setSpeed(150);
  motor2->setSpeed(150);
  motor3->setSpeed(150);
  motor4->setSpeed(150);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}




