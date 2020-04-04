#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <math.h>  

ros::Publisher speed_pub;
geometry_msgs::Twist speedMsg;

int flag;
double marker;
double initPx;
double initPy;

void poseCallback(const nav_msgs::Odometry::ConstPtr& odomMsg){
	
    if (flag == 0){
        initPx = odomMsg->pose.pose.position.x;
        initPy = odomMsg->pose.pose.position.y;
        flag = 1;
    }
    
    else if (marker <= 1.0){
	speedMsg.linear.x = 0.1;
	marker = fabs(odomMsg->pose.pose.position.x-initPx);
    }
		
    else if(marker > 1.0){
	speedMsg.linear.x = -0.1;
    } 

    ROS_INFO("Difference: %f, Vx-> %f\n", fabs(odomMsg->pose.pose.position.x-initPx), speedMsg.linear.x);
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
