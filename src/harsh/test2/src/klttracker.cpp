//This code is for KLT tracker//

//Code from image_converter.cpp
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
//

/*
//code from tutorial
#include <visp/vpImageConvert.h>
#include <visp/vpKltOpencv.h>
#include <visp/vpDisplayOpenCV.h>
#include <visp/vpVideoReader.h>
//

//code from tutorial-image-converter.cpp//
#include <visp/vpImageIo.h>
#include <visp/vpImageConvert.h>
*/

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
	
}

int main(int argc, char **argv)  //standard line
{
  ros::init(argc, argv, "klttracker");  //standard line
  ros::NodeHandle n;   //standard line 

  // Subscriber
 ros::Subscriber sub = n.subscribe("/camera/image_raw", 1000, imageCallback);
 //Converting ROS Image into OpenCV Mat
 cv::Mat img;
 convertToMat(x,img);  

/*
 vpImage<unsigned char> I;
 vpImageConvert::convert(img, I);

 IplImage * cvI = NULL;
 vpImageConvert::convert(I, cvI);

#if (VISP_HAVE_OPENCV_VERSION >= 0x010100) && defined(VISP_HAVE_FFMPEG)
 //vpVideoReader reader;
 // reader.setFileName("video2.mpeg");

 // vpImage<unsigned char> I;
 // reader.acquire(I);

 // IplImage * cvI = NULL;
 // vpImageConvert::convert(I, cvI);
  
  // Display initialisation
  vpDisplayOpenCV d(I, 0, 0, "Klt tracking");
  vpDisplay::display(I);

  
  vpKltOpencv tracker;
  // Set tracker parameters
  tracker.setMaxFeatures(200);
  tracker.setWindowSize(10);
  tracker.setQuality(0.01);
  tracker.setMinDistance(15);
  tracker.setHarrisFreeParameter(0.04);
  tracker.setBlockSize(9);
  tracker.setUseHarris(1);
  tracker.setPyramidLevels(3);

  // Initialise the tracking
  tracker.initTracking(cvI);

  tracker.track(cvI);
  tracker.display(I, vpColor::red);
  vpDisplay::flush(I);

  /*while ( ! reader.end() )
  {
    reader.acquire(I);
    vpDisplay::display(I);

    vpImageConvert::convert(I, cvI);
    tracker.track(cvI);

    tracker.display(I, vpColor::red);
    vpDisplay::flush(I);
  }

  vpDisplay::getClick(I);

  cvReleaseImage(&cvI);
*/
  return 0;
// #endif
}
