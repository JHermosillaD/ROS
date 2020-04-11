#include <ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <SR04.h>
#include <pitches.h>
#define TRIG_PIN 12
#define ECHO_PIN 11
// Driven wheels
#define motorPinD1 5;   // Pin 14 of L293
#define motorPinD2 6;   // Pin 10 of L293
// Rotation wheels
#define motorPinR1 10;  // Pin  7 of L293
#define motorPinR2 9;   // Pin  2 of L293

ros::NodeHandle n_C;
ros::NodeHandle n_R;
std_msgs::String Control;
std_msgs::Float64 Range;
ros::Publisher Velocity("Velocity",&Control);
ros::Publisher Ultrasonic("Ultrasonic",&Range);

// SR04
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

// notes in the melody:
int melody[] = { NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6 };
int duration = 500;  // 500 miliseconds

void setup(){

    n_C.initNode();
    n_R.initNode();
    n_R.advertise(Ultrasonic);
    n_C.advertise(Velocity);
    Serial.begin(57600);
    
    //Set pins as outputs
    pinMode(motorPinD1, OUTPUT);
    pinMode(motorPinD2, OUTPUT);
    pinMode(motorPinR1, OUTPUT);
    pinMode(motorPinR2, OUTPUT);

    //Set speed control
    int speedD = 80;            // 0-255  
    int speedR = 50;            // 0-255
    
    delay(1000);   
    
}

void loop(){

    // Ultrasonic range measure
    a=sr04.Distance();
    Range.data= a;
    Ultrasonic.publish(&Range);
    
    // Motion Control

    if( Range >= 10.0 || Range != Range ){
      analogWrite(motorPinD1, speedD);
      analogWrite(motorPinD2, speedD);
      digitalWrite(motorPinR1, LOW);
      digitalWrite(motorPinR2, LOW);
      Control = " Straight line ";
    }
    else{
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        // pin8 output the voice, every scale is 0.5 sencond
        tone(8, melody[thisNote], duration);
      }
      analogWrite(motorPinD1, speedR);
      analogWrite(motorPinD2, speedR);
      analogWrite(motorPinR1, speedR);
      analogWrite(motorPinR2, speedR);
      Control = " Rotating ";
    }

    Velocity.publish(&Control);
    ROS_INFO("Range -> %f, Status -> %s\n", Range, Control );

    n_R.spinOnce();
    n_C.spinOnce();
    delay(1000);
    
}
