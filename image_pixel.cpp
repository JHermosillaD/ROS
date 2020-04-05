#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/CameraInfo.h"
#include "sensor_msgs/Image.h"
#include <std_msgs/Int8.h>
#include "math.h"

ros::Publisher color_selection_pub;
int k = 640*480*3;
int R,Y,B;
int color;

void imageCallback(const sensor_msgs::Image::ConstPtr& image){

	std_msgs::Int8 msg;

	for (int i=0 ; i<k ; i=i+3){
		if (((image->data[i+2]) > 100) && ((image->data[i+1]) < 60) && ((image->data[i]) < 60)){
			R++;
		}
		else if (((image->data[i+2]) > 100) && ((image->data[i+1]) > 100) && ((image->data[i]) < 60)){
			Y++;
		}
		else if (((image->data[i+2]) < 60) && ((image->data[i+1]) < 60) && ((image->data[i]) > 100)){
			B++;
		}	
	}

	if (R>B){
		if(R>Y){
			msg.data = 0;
		}
		else {
			msg.data = 1;
		}
	}
	else if (B>R){
		if(B>Y){
			msg.data = 2;
		}
		else{
			msg.data = 1;
		}
	}
	
	printf("%i\n",msg);
	color_selection_pub.publish(msg);
}

int main(int argc, char**argv){
	
	ros::init(argc, argv, "color_selection");
	ros::NodeHandle n_c;
	ros::NodeHandle n_s;
	ros::Subscriber sub = n_c.subscribe("/camera/rgb/image_raw", 100,imageCallback);
	color_selection_pub = n_s.advertise<std_msgs::Int8>("chatter", 1000);
	ros::spin();
	return 0;
	
}
