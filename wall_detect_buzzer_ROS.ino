#include <ros.h>
#include <std_msgs/Float64.h>
#include <SR04.h>
#include <pitches.h>
#define TRIG_PIN 12
#define ECHO_PIN 11

ros::NodeHandle n_R;
std_msgs::Float64 Range;
ros::Publisher Ultrasonic("Ultrasonic",&Range);

// SR04
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

//Motor A
const int motorPinD1  = 5;  // Pin 14 of L293
const int motorPinD2  = 6;  // Pin 10 of L293
//Motor B
const int motorPinR1  = 10; // Pin  7 of L293
const int motorPinR2  = 9;  // Pin  2 of L293

// notes in the melody:
int melody[] = { NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6 };
int duration = 500;  // 500 miliseconds

//Set speed control
int speedD = 80;            // 0-255  
int speedR = 50;            // 0-255

void setup(){
  
    n_R.initNode();
    n_R.advertise(Ultrasonic);
  
   Serial.begin(57600);
    
    //Set pins as outputs
    pinMode(motorPinD1, OUTPUT);
    pinMode(motorPinD2, OUTPUT);
    pinMode(motorPinR1, OUTPUT);
    pinMode(motorPinR2, OUTPUT);
    
}
void loop(){

    // Ultrasonic range measure
    a=sr04.Distance();
    Range.data= a;
    Ultrasonic.publish(&Range);
    
    // Motion Control

    if( a >= 10.0 || a == 0){
      digitalWrite(motorPinD1, HIGH);
      digitalWrite(motorPinD2, LOW);
      digitalWrite(motorPinR1, LOW);
      digitalWrite(motorPinR2, LOW);
    }
    else{
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        // pin8 output the voice, every scale is 0.5 sencond
        tone(8, melody[thisNote], duration);
      }
      digitalWrite(motorPinD1, LOW);
      digitalWrite(motorPinD2, LOW);
      digitalWrite(motorPinR1, LOW);
      digitalWrite(motorPinR2, HIGH);
      }
      
    n_R.spinOnce();    
    
}
