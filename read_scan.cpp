#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "math.h"

ros::Publisher speed_pub;
geometry_msgs::Twist speedMsg;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan){

	if (scan->ranges[320] > 1.0 || scan->ranges[320] != scan->ranges[320]){
		speedMsg.linear.x = 0.2;
	}

	else if (scan->ranges[320] < 1.0 || scan->ranges[320] != scan->ranges[320]){
		speedMsg.linear.x = 0.0;
	}
	
	ROS_INFO("%f\n",scan->ranges[320]);
	speed_pub.publish(speedMsg);

}

int main(int argc, char**argv){

	ros::init(argc, argv, "scan_along_x");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/scan", 50,scanCallback);
	speed_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1000);
	ros::spin();

return 0;

}

