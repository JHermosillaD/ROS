#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <std_msgs/Int8.h>
#include "math.h"

ros::Publisher goal 
float x_in;
float y_in;
int flag;

void ReactCallback(const std_msgs::Int8::ConstPtr& msg){

	move_base_msgs::MoveBaseActionGoal goalmsg;
	goalmsg.goal.target_pose.header.frame_id = "map";

    if (msg->data==0){
		goalmsg.goal.target_pose.pose.position.x = 0.23;
		goalmsg.goal.target_pose.pose.position.y = -0.5;
    }
    else {
		goalmsg.goal.target_pose.pose.position.x = 0.026;
		goalmsg.goal.target_pose.pose.position.y = 1.07;
		x_in = 0.026;
		y_in = 1.07 ;
    }
    
	goal.publish(goalmsg);

}

int main(int argc, char**argv){

	ros::init(argc, argv, "react");
	ros::NodeHandle n;
	ros::NodeHandle ngoal;
	ros::Subscriber sub = n.subscribe("chatter", 1000,ReactCallback);
	goal = ngoal.advertise<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 1000);
	ros::spin();
	return 0;

}
