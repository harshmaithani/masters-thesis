// ROS includes.
#include <ros/ros.h>

// Messages
#include <std_msgs/Int8.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/JointState.h>

//#include <icl_core/EnumHelper.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h>

// Namespace
using namespace std;


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

int pose;


int main(int argc, char **argv) {
	// Set up ROS.
	ros::init(argc, argv, "contact_poses_node");
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
	while (nh.ok()){
		// Only when toggled on (std empty message)
		if (running){
      			// Get a normalized time
      			if ((ros::Time::now() - counter) > ros::Duration(sin_duration)){
       				counter = ros::Time::now();
			}
			else {
				normalized_time = (ros::Time::now() - counter).toSec() / sin_duration;
			}

			// Publish channel positions in RAD.
			// Everything is 0 by default

			for (size_t channel = 0; channel < 9; ++channel){
				double cur_pos = 0.0;
				channel_pos.position[channel] = cur_pos;
			}

			while (1) {
				cout<<"Please enter the grasp sequence, press 0 for terminating";
				cin>>pose;
				if(pose==0){
					break;
				}
				else{   
					
					//Normal state

					/*
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
					//break;

					usleep(2000000);
                                        */


					switch (pose) {

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
							
						case 2: //Thumb flexion

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
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
							
						case 3: //Index_Finger_Proximal

							channel_pos.position[0] =0;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0.4; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														

							channel_pos_pub.publish(channel_pos);
							break;
							
						case 4: //Index_Finger_Distal

							channel_pos.position[0] =0;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0.65;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";			
							
							channel_pos_pub.publish(channel_pos);
							break;
							
						case 5: //Index_Finger_Proximal + Distal

							channel_pos.position[0] =0;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0.65;// "Index_Finger_Distal";
							channel_pos.position[3] =0.4; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;
							
						case 6: //Middle_Finger_Proximal

							channel_pos.position[0] =0;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0.4; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
							
							channel_pos_pub.publish(channel_pos);
							break;
							
						case 7: //Middle_Finger_Distal

							channel_pos.position[0] =0;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0.65; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
													
							
							channel_pos_pub.publish(channel_pos);
							break;
							
						case 8: //Middle_Finger_Proximal+Distal

							channel_pos.position[0] =0;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0.65; //"Middle_Finger_Distal";
							channel_pos.position[5] =0.4; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;
							
						case 9: //Ring finger

							channel_pos.position[0] =0;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0.45; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;
							
						case 10: //Pinky

							channel_pos.position[0] =0;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0.45; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;

						case 11: //Thumb and Index proximal

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0.4; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;
						
						case 12: //Thumb and Index distal
		
							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0.65;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;
						
						case 13: //Thumb, Index proximal and Index distal

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0.65;// "Index_Finger_Distal";
							channel_pos.position[3] =0.4; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;

						case 14: //Thumb and Middle proximal

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0.4; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;

						case 15: //Thumb and Middle distal

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0.65; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;

						case 16: //Thumb, Middle proximal and Middle distal

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0.65; //"Middle_Finger_Distal";
							channel_pos.position[5] =0.4; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;

						case 17: //Thumb, Index and Middle proximal

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0;// "Index_Finger_Distal";
							channel_pos.position[3] =0.4; //"Index_Finger_Proximal";
							channel_pos.position[4] =0; //"Middle_Finger_Distal";
							channel_pos.position[5] =0.4; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;

						case 18: //Thumb, Index and Middle distal

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0.65;// "Index_Finger_Distal";
							channel_pos.position[3] =0; //"Index_Finger_Proximal";
							channel_pos.position[4] =0.65; //"Middle_Finger_Distal";
							channel_pos.position[5] =0; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;

						case 19: //Thumb, Index and Middle proximal and distal

							channel_pos.position[0] =0.45;//"Thumb_Flexion";
							channel_pos.position[1] =0;//"Thumb_Opposition";
							channel_pos.position[2] =0.65;// "Index_Finger_Distal";
							channel_pos.position[3] =0.4; //"Index_Finger_Proximal";
							channel_pos.position[4] =0.65; //"Middle_Finger_Distal";
							channel_pos.position[5] =0.4; //"Middle_Finger_Proximal";
							channel_pos.position[6] =0; //"Ring_Finger";
							channel_pos.position[7] =0; //"Pinky";
							channel_pos.position[8] =0.5; //"Finger_Spread";
														
							
							channel_pos_pub.publish(channel_pos);
							break;
					}
				}

			} //end of while(1)

			rate.sleep();
			ros::spinOnce();

			return 0;
		} //end of if
	} //end of while (nh.ok())
} //end of main
