#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "tf/tf.h"
#include "geometry_msgs/Pose2D.h"
#include "nav_msgs/Odometry.h"
#include <math.h>  

ros::Publisher speed_pub; 
geometry_msgs::Twist speedMsg; 

int flag = 0;
double roll, pitch, yaw;
double initPx;
double initPy;
double inityaw;
double yaw_degrees;
double inityaw_degrees;

void poseCallback(const nav_msgs::Odometry::ConstPtr& odomMsg){
	
    // Quaternion to RPY conversion
    tf::Quaternion q(
        odomMsg->pose.pose.orientation.x,
        odomMsg->pose.pose.orientation.y,
        odomMsg->pose.pose.orientation.z,
        odomMsg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    m.getRPY(roll, pitch, yaw);
    
	// Initial conditions
    if (flag == 0){
        initPx =  odomMsg->pose.pose.position.x;
        initPy =  odomMsg->pose.pose.position.y;
        inityaw = yaw;
        flag = 1;
    }
    
    // Angular positions
	yaw_degrees = yaw * 180.0 / M_PI; 
	if( yaw_degrees < 0 ) { 							// convert negative to positive angles
		yaw_degrees += 360.0; 
	}
	
	inityaw_degrees = inityaw * 180.0 / M_PI;
	if( inityaw_degrees < 0 ) {
		inityaw_degrees += 360.0; 						// convert negative to positive angles
	}
		
	if( fabs(yaw_degrees - inityaw_degrees) <= 90.0) {
		speedMsg.linear.x = 0.0;
        speedMsg.angular.z = 0.2;
    }
	else {
		speedMsg.linear.x = 0.0;
        speedMsg.angular.z = 0.0;
	}

	ROS_INFO("Initial angle -> %f, Current angle -> %f, Angular displacement -> %f\n", inityaw_degrees, yaw_degrees, fabs(yaw_degrees - inityaw_degrees) );

    speed_pub.publish(speedMsg);
    
}

int main(int argc, char**argv)
{
  ros::init(argc, argv, "odom_pub");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/odom", 1000,poseCallback);
  speed_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1000);
  ros::spin();
  return 0;
}
