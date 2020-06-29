// ROS includes.
#include <ros/ros.h>

// Messages
#include <std_msgs/Int8.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/JointState.h>

#include <icl_core/EnumHelper.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h>

#include "SVHNode.h"


// Consts
// Loop Rate (i.e Frequency) of the ROS node -> 50 = 50HZ
const double loop_rate = 50;
// Time of a half Sin. i.e. 10 = In 10 Seconds the selected fingers will perform a close and open (Sin to 1PI)
const double sin_duration = 10;


// Local Vars
bool running = true;
/*--------------------------------------------------------------------
 * Callback functions
 *------------------------------------------------------------------*/
// Toggle on off
void runCallback(const std_msgs::Empty&)
{
  running = !running;
}
/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int counter1;
int tracker=0;
int localvalue;
int graspmatrix[20]={};


int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "svh_sine_test");
  ros::NodeHandle nh("~");

  // Subscribe connect topic (Empty)
  ros::Subscriber run_sub = nh.subscribe("toggle_run", 1, runCallback);

  // Publish current target positions
  ros::Publisher channel_pos_pub = nh.advertise<sensor_msgs::JointState>("channel_targets", 1);

  // joint state message template
  sensor_msgs::JointState channel_pos;
  channel_pos.name.resize(9);
  channel_pos.position.resize(9, 0.0);

  // Pre Fill the Names of the Finger
  channel_pos.name[0] = "Thumb_Flexion";
  channel_pos.name[1] = "Thumb_Opposition";
  channel_pos.name[2] = "Index_Finger_Distal";
  channel_pos.name[3] = "Index_Finger_Proximal";
  channel_pos.name[4] = "Middle_Finger_Distal";
  channel_pos.name[5] = "Middle_Finger_Proximal";
  channel_pos.name[6] = "Ring_Finger";
  channel_pos.name[7] = "Pinky";
  channel_pos.name[8] = "Finger_Spread";

  // Set up the normalized time
  ros::Time counter = ros::Time::now();
  double normalized_time = 0;

  // Init the Random
  srand (time(NULL));

  // Tell ROS how fast to run this node. (100 = 100 Hz = 10 ms)
  ros::Rate rate(50);

  // Main loop.
  while (nh.ok())
  {
    // Only when toggled on (std empty message)
    if (running)
    {
      // Get a normalized time
      if ((ros::Time::now() - counter) > ros::Duration(sin_duration))
      {
        counter = ros::Time::now();
      }
      else
      {
        normalized_time = (ros::Time::now() - counter).toSec() / sin_duration;
      }

      // Publish channel positions in RAD.
      // Everything is 0 by default






      for (size_t channel = 0; channel < 9; ++channel)
      {

        double cur_pos = 0.0;

        channel_pos.position[channel] = cur_pos;
      }


ask:

//std::cout<<"Enter the grasp number";
//std::cin>>localvalue;


tracker=0;
graspmatrix[20]={};

while (counter1==0)
   {
        std::cout<<"Please enter the grasp sequence , press 0 for terminating";
        std::cin>>localvalue;
        if (localvalue==0)
        {
            counter1=1;
        }
        else
        {
        graspmatrix[tracker]=localvalue;
        tracker=tracker+1;
        }

    break;
}




for (int i=0;i<tracker;i=i+1)
 {
    int b=graspmatrix[i];

    switch (b) //(localvalue)
      {
      case 0: //Empty
      goto ask;

      case 1: //Normal state

        channel_pos.position[0] =0;//"Thumb_Flexion";
        channel_pos.position[1] =0;//"Thumb_Opposition";
        channel_pos.position[2] =0;// "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.5; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 2: //Fingers wide open

          channel_pos.position[0] =0; //"Thumb_Flexion";
          channel_pos.position[1] =0; //"Thumb_Opposition";
          channel_pos.position[2] =0; // "Index_Finger_Distal";
          channel_pos.position[3] =0; //"Index_Finger_Proximal";
          channel_pos.position[4] =0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0; //"Ring_Finger";
          channel_pos.position[7] =0; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 3: //Fist

          channel_pos.position[0] =0.3; //"Thumb_Flexion";
          channel_pos.position[1] =0.1; //"Thumb_Opposition";
          channel_pos.position[2] =1.3; // "Index_Finger_Distal";
          channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
          channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0.9; //"Ring_Finger";
          channel_pos.position[7] =0.9; //"Pinky";
          channel_pos.position[8] =0.5; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 4: //2 finger pinch , not successful

          channel_pos.position[0] =0; //"Thumb_Flexion";
          channel_pos.position[1] =0; //"Thumb_Opposition";
          channel_pos.position[2] =1.0; // "Index_Finger_Distal";
          channel_pos.position[3] =0.3; //"Index_Finger_Proximal";
          channel_pos.position[4] =1.0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.3; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0; //"Ring_Finger";
          channel_pos.position[7] =0; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 5: //Configuraton 1

          channel_pos.position[0] =0; //"Thumb_Flexion";
          channel_pos.position[1] =0; //"Thumb_Opposition";
          channel_pos.position[2] =0; // "Index_Finger_Distal";
          channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
          channel_pos.position[4] =0.0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0.4; //"Ring_Finger";
          channel_pos.position[7] =0.2; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 6: //Holding book

          channel_pos.position[0] =0.5; //"Thumb_Flexion";
          channel_pos.position[1] =0; //"Thumb_Opposition";
          channel_pos.position[2] =0; // "Index_Finger_Distal";
          channel_pos.position[3] =0.5; //"Index_Finger_Proximal";
          channel_pos.position[4] =0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.5; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0.4; //"Ring_Finger";
          channel_pos.position[7] =0.2; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 7: //Configuration 3 support with side of thumb

          channel_pos.position[0] =0.9; //"Thumb_Flexion";
          channel_pos.position[1] =0; //"Thumb_Opposition";
          channel_pos.position[2] =0; // "Index_Finger_Distal";
          channel_pos.position[3] =0; //"Index_Finger_Proximal";
          channel_pos.position[4] =0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0; //"Ring_Finger";
          channel_pos.position[7] =0; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);

          channel_pos.position[0] =0.9; //"Thumb_Flexion";
          channel_pos.position[1] =0; //"Thumb_Opposition";
          channel_pos.position[2] =1.3; // "Index_Finger_Distal";
          channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
          channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0.9; //"Ring_Finger";
          channel_pos.position[7] =0.7; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 8: //holding plate

          channel_pos.position[0] =0.5; //"Thumb_Flexion";
          channel_pos.position[1] =0.9; //"Thumb_Opposition";
          channel_pos.position[2] =0; // "Index_Finger_Distal";
          channel_pos.position[3] =0.5; //"Index_Finger_Proximal";
          channel_pos.position[4] =0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.5; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0.2; //"Ring_Finger";
          channel_pos.position[7] =0.2; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 9: //small clasp

          channel_pos.position[0] =0; //"Thumb_Flexion";
          channel_pos.position[1] =0; //"Thumb_Opposition";
          channel_pos.position[2] =0.5; // "Index_Finger_Distal";
          channel_pos.position[3] =0.5; //"Index_Finger_Proximal";
          channel_pos.position[4] =0.5; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.5; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0; //"Ring_Finger";
          channel_pos.position[7] =0; //"Pinky";
          channel_pos.position[8] =0.4; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 10: //pipe clasping

          channel_pos.position[0] =0; //"Thumb_Flexion";
          channel_pos.position[1] =0; //"Thumb_Opposition";
          channel_pos.position[2] =0; // "Index_Finger_Distal";
          channel_pos.position[3] =0; //"Index_Finger_Proximal";
          channel_pos.position[4] =0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0; //"Ring_Finger";
          channel_pos.position[7] =0; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          usleep(1000000);

          channel_pos.position[0] =0.9; //"Thumb_Flexion";
          channel_pos.position[1] =0.9; //"Thumb_Opposition";
          channel_pos.position[2] =0; // "Index_Finger_Distal";
          channel_pos.position[3] =0; //"Index_Finger_Proximal";
          channel_pos.position[4] =0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0.9; //"Ring_Finger";
          channel_pos.position[7] =0; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          usleep(1000000);

          channel_pos.position[0] =0.9; //"Thumb_Flexion";
          channel_pos.position[1] =0.9; //"Thumb_Opposition";
          channel_pos.position[2] =0; // "Index_Finger_Distal";
          channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
          channel_pos.position[4] =0; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0.9; //"Ring_Finger";
          channel_pos.position[7] =0; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);

          usleep(1000000);
          channel_pos.position[0] =0.9; //"Thumb_Flexion";
          channel_pos.position[1] =0.9; //"Thumb_Opposition";
          channel_pos.position[2] =1.3; // "Index_Finger_Distal";
          channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
          channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
          channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
          channel_pos.position[6] =0.9; //"Ring_Finger";
          channel_pos.position[7] =0.9; //"Pinky";
          channel_pos.position[8] =0.7; //"Finger_Spread";

          channel_pos_pub.publish(channel_pos);
          break;

      case 11: // can

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);

        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);

        break;

     case 12: //Precision grasp

        channel_pos.position[0] =0.32; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";0.67
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.3; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0.32; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.19; // "Index_Finger_Distal";
        channel_pos.position[3] =0.2; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.3; //"Finger_Spread";
        channel_pos_pub.publish(channel_pos);

        break;

    case 13: // Coin
	
	usleep(1000000);
        channel_pos.position[0] =0.0; //"Thumb_Flexion";
        channel_pos.position[1] =0.0; //"Thumb_Opposition";
        channel_pos.position[2] =0.94; // "Index_Finger_Distal";
        channel_pos.position[3] =0.80; //"Index_Finger_Proximal";
        channel_pos.position[4] =0.94; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.80; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        usleep(1000000);

        channel_pos.position[0] =0.40; //"Thumb_Flexion";
        channel_pos.position[1] =0; //"Thumb_Opposition";
        channel_pos.position[2] =0.94; // "Index_Finger_Distal";
        channel_pos.position[3] =0.80; //"Index_Finger_Proximal";
        channel_pos.position[4] =0.94; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.80; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);

        break;

   case 14: //Tight test

        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);

        break;

    case 15 : // orange

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.5; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        usleep(1000000);

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.5; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        usleep(1000000);

        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.5; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);

        break;

    case 161: //power grasp

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.3; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        //usleep(10000000);
	
	break;
    
    case 162:
      
        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =1.3; //"Middle_Finger_Distal";

        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.3; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);

        break;

      case 17: // Zero state

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        break;


    case 18: // Pen


        // finger spread =0.7 ,thumb opposition = 0.9
        // middle finger proximal =0.80  distal = 0
        // thumb flexion = 0.42
        // finger spread =
        // index finger distal = 1.28 proximal = 0.29
        // finger spread = 0

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";
        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0.42; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";
        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0.42; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.3; //"Finger_Spread";
        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0.42; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.3; //"Finger_Spread";
        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0.42; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.3; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.3; //"Finger_Spread";
        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0.42; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.3; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0; //"Finger_Spread";
        channel_pos_pub.publish(channel_pos);

        break;

    case 19:

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
        usleep(10000000);

        channel_pos.position[0] =0.; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";
        channel_pos_pub.publish(channel_pos);
         usleep(10000000);

         channel_pos.position[0] =0.9; //"Thumb_Flexion";
         channel_pos.position[1] =0.9; //"Thumb_Opposition";
         channel_pos.position[2] =0; // "Index_Finger_Distal";
         channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
         channel_pos.position[4] =0; //"Middle_Finger_Distal";
         channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
         channel_pos.position[6] =0.9; //"Ring_Finger";
         channel_pos.position[7] =0.9; //"Pinky";
         channel_pos.position[8] =0.7; //"Finger_Spread";
         channel_pos_pub.publish(channel_pos);
         usleep(10000000);

         channel_pos.position[0] =0.9; //"Thumb_Flexion";
         channel_pos.position[1] =0.9; //"Thumb_Opposition";
         channel_pos.position[2] =1.3; // "Index_Finger_Distal";
         channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
         channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
         channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
         channel_pos.position[6] =0.9; //"Ring_Finger";
         channel_pos.position[7] =0.9; //"Pinky";
         channel_pos.position[8] =0.7; //"Finger_Spread

         channel_pos_pub.publish(channel_pos);

        break;

	case 20:

	channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread";

        channel_pos_pub.publish(channel_pos);
	break;

        case 21: //Couscous box-I

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.25; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
	break;

        case 22: //Couscous-II
 
        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =1.3; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.25; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
	break;
        
        case 23: //Cup-I
 
        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.25; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
         break;
         
         case 24: //Cup-II

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.4; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
	
        usleep(10000000);

        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.4; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
	break;

        case 25: // Spray bottle Not complete
 
        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.4; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
        usleep(10000000);

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.4; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
        usleep(10000000);

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.4; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);

        usleep(10000000);

        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0; //"Ring_Finger";
        channel_pos.position[7] =0; //"Pinky";
        channel_pos.position[8] =0.4; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
        usleep(10000000);

        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0.8; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0.8; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.4; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
        break;

        case 26: //orange-I
 
        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.25; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
        usleep(10000000);
     
        channel_pos.position[0] =0; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0.7; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0.5; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);

        break;
        
        case 27://orange-II
     
        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =0.7; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0.5; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
        break;

        case 28://orange-III
     
        channel_pos.position[0] =0.9; //"Thumb_Flexion";
        channel_pos.position[1] =0.9; //"Thumb_Opposition";
        channel_pos.position[2] =1.3; // "Index_Finger_Distal";
        channel_pos.position[3] =0; //"Index_Finger_Proximal";
        channel_pos.position[4] =0.5; //"Middle_Finger_Distal";
        channel_pos.position[5] =0; //"Middle_Finger_Proximal";
        channel_pos.position[6] =0.9; //"Ring_Finger";
        channel_pos.position[7] =0.9; //"Pinky";
        channel_pos.position[8] =0.7; //"Finger_Spread"; 

        channel_pos_pub.publish(channel_pos);
        
        break;
        

      }

    //usleep(10000);
}

//usleep(tracker*10000000);

goto ask;

      // Publish

    } //end of while loop

    rate.sleep();
    ros::spinOnce();

    // TO INDTRODUCE A VARIIING TIME RATE (in This case 50 - 100 HZ ) Uncomment this (discouraged! Will result in strange things obiously)
    // Was meant to test jitter in the trajectory generation
    //rate = 50+(rand() % 10 )*5;


  return 0;
    }

}// end main()
