// %Tag(FULLTEXT)%

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <cstdlib> // needed for getenv()
#include <ros/package.h>
#include <sensor_msgs/Image.h>

#include "image_transport/image_transport.h"
#include "cv_bridge/cv_bridge.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//This code is for converting an image from ROS sensor_msgs/Image to OpenCV IPL format 


// * This will read from the uEye camera
sensor_msgs::Image x;


void imageCallback(const sensor_msgs::Image::ConstPtr& msg)
{  
  //ROS_INFO("I heard: [%s]", msg->data.c_str());//
   ROS_INFO("I can see !");
   x=(*msg);
 
}

void convertToMat(sensor_msgs::Image imgROS, cv::Mat& imgCV)
{

 cv_bridge::CvImagePtr cv_ptr;
 try
    {
      cv_ptr = cv_bridge::toCvCopy(imgROS, sensor_msgs::image_encodings::MONO8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
 
 cv_ptr->image.copyTo(imgCV); 

 cv::imshow("Image in OpenCV",imgCV);
 cv::waitKey(1);
	
}

int main(int argc, char **argv)  //standard line
{
  ros::init(argc, argv, "image_converter");  //standard line
  ros::NodeHandle n;   //standard line 

  // Subscriber
 ros::Subscriber sub = n.subscribe("/camera/image_raw", 1000, imageCallback);

  //ros::spin(); 

 ros::Publisher pub = n.advertise<sensor_msgs::Image>("harsh", 1000);
 
  ros::Rate loop_rate(10);

  int count = 0;
  cv::Mat img;

  while (ros::ok())
   {
   ROS_INFO("Hi");
   
   //convert to openCV mat
   convertToMat(x,img);   
	
   pub.publish(x);
   ros::spinOnce();
   loop_rate.sleep();
    }

  return 0;
}

