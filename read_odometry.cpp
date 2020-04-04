#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <math.h>  

ros::Publisher speed_pub;
geometry_msgs::Twist speedMsg;
int flag=0;
double marker1=0;
double marker2=0;
double initPx;
double initPy;

void poseCallback(const nav_msgs::Odometry::ConstPtr& odomMsg)
{
    if (flag == 0){
        initPx = odomMsg->pose.pose.position.x;
        initPy = odomMsg->pose.pose.position.y;
        flag = 1;
    }
    
    if (marker1 <= 1.0 && marker2 <= 0){
		speedMsg.linear.x = 0.4;
		marker1 = fabs(odomMsg->pose.pose.position.x-initPx);
	}
	else if(marker1 > 1.0 && marker2 <= 1 ){
		speedMsg.linear.x = -0.1;
		marker2 = fabs(odomMsg->pose.pose.position.x-initPx);
	} 
	ROS_INFO("Difference %f, X Velocity %f, Xo Position %f\n", marker1, speedMsg.linear.x, initPx);
    speed_pub.publish(speedMsg);
    
}

int main(int argc, char**argv)
{
  ros::init(argc, argv, "publisher");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/odom", 1000,poseCallback);

  speed_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1000);
  ros::spin();
  return 0;
}
