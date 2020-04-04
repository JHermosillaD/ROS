#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <math.h>

int main(int argc, char**argv){
	
	ros::init(argc, argv, "my_fisrt_node");
	ros::NodeHandle n;
	ros::Publisher speed_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1000);
	ros::Rate loop_rate(10);
	
	double v = 1.0;
	double angulo = 38.0;
	double w = angulo*M_PI/180.0;
	
	while (ros::ok()){
		
		while(v > 0){
			geometry_msgs::Twist speedMsg;
			speedMsg.linear.x= v;
			speedMsg.angular.z= w;
			v -=  0.001;
			ROS_INFO("V-> %f, W-> %f\n", v, w);
			speed_pub.publish(speedMsg);
			loop_rate.sleep();
			ros::spinOnce();
		}
	}
	
	return 0;
}
