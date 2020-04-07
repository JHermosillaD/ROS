#include <ros.h>
#include <std_msgs/Float64.h>
#include <SR04.h>
#define TRIG_PIN 12
#define ECHO_PIN 11

ros::NodeHandle n;
std_msgs::Float64 Range;
ros::Publisher ultrasonic("ultrasonic",&Range);

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

void setup() {

	n.initNode();
	n.advertise(ultrasonic);
	Serial.begin(57600);
	delay(1000);

}

void loop() {

	a=sr04.Distance();
	Range.data= a;
	ultrasonic.publish(&Range);
	//ROS_INFO(" Rango -> %f\n" , a); 
	n.spinOnce();
	delay(1000);
}
