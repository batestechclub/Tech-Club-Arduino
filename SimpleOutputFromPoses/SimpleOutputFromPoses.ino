#include <MyoController.h>

#define FIST_PIN 4
#define WAVEIN_PIN 5
#define WAVEOUT_PIN 6
#define FINGERSSPREAD_PIN 7
#define DOUBLETAP_PIN 8

MyoController myo = MyoController();

void setup() {
  
  pinMode(FIST_PIN, OUTPUT);
  pinMode(WAVEIN_PIN, OUTPUT);
  pinMode(WAVEOUT_PIN, OUTPUT);
  pinMode(FINGERSSPREAD_PIN, OUTPUT);
  pinMode(DOUBLETAP_PIN, OUTPUT);

  pinMode(13, OUTPUT);
  
  myo.initMyo();
}

void loop()
{

   myo.updatePose();
   
   switch ( myo.getCurrentPose() ) {
    case rest:
      digitalWrite(FIST_PIN,LOW); 
      digitalWrite(WAVEIN_PIN,LOW);
      digitalWrite(WAVEOUT_PIN,LOW);
      digitalWrite(FINGERSSPREAD_PIN,LOW);
      digitalWrite(DOUBLETAP_PIN,LOW);

      Serial.println("rest");
      
      break;
    case fist:
      digitalWrite(FIST_PIN,HIGH);
      //Turn on LED
      digitalWrite(13,HIGH);
      Serial.println("fist");
      break;
    case waveIn:
      digitalWrite(WAVEIN_PIN,HIGH);
      Serial.println("wave in");
      break;
    case waveOut:
      digitalWrite(WAVEOUT_PIN,HIGH);
      Serial.println("wave out");
      break;
    case fingersSpread:
      digitalWrite(FINGERSSPREAD_PIN,HIGH);
      Serial.println("fingers spread");
      digitalWrite(13,LOW);
      break;
    case doubleTap:
      digitalWrite(DOUBLETAP_PIN,HIGH);
      Serial.println("double tap");
      break;
   } 
   
   delay(100);
}
