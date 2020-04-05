#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "math.h"

ros::Publisher speed_pub;
geometry_msgs::Twist speedMsg;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan){
	
/*
int contador = 0;
double theta = 90.0; 
double radians = 0;
radians = (theta*M_PI)/180.0;
*/

	int ranges = scan->ranges.size();
	for(int i = 0; i < ranges; ++i){

		if( scan->ranges[320] > 1.25 || scan->ranges[320] != scan->ranges[320] ){
			speedMsg.linear.x = 0.3;
			speedMsg.angular.z = 0.0;
		}
		else{
			speedMsg.linear.x = 0.0;
			speedMsg.angular.z = 0.6; 
		}
		
	speed_pub.publish(speedMsg);

	}
}

int main(int argc, char**argv){

	ros::init(argc, argv, "in_square_node");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/scan", 50,scanCallback);
	speed_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1000);
	ros::spin();
	return 0;

}
