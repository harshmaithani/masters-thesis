// %Tag(FULLTEXT)%
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <cstdlib> // needed for getenv()
#include <ros/package.h>
#include <sensor_msgs/Image.h>


// * This will read from the uEye camera
sensor_msgs::Image x;

void callback1(const sensor_msgs::Image::ConstPtr& msg)
{  
  //ROS_INFO("I heard: [%s]", msg->data.c_str());//
   ROS_INFO("I can see !");

x=(*msg);

}

int main(int argc, char **argv)  //standard line
{
  ros::init(argc, argv, "listener");  //standard line
  ros::NodeHandle n;   //standard line

// Subscriber
ros::Subscriber sub = n.subscribe("/camera/image_raw", 1000, callback1);

//ros::spin();

ros::Publisher pub = n.advertise<sensor_msgs::Image>("harsh", 1000);

ros::Rate loop_rate(10);

int count = 0;

while (ros::ok())
  {

ROS_INFO("Hi");
pub.publish(x);

ros::spinOnce();
loop_rate.sleep();

}

  return 0;
}

