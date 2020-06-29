/* Leap motion bridge 
 * Subscribe to Ros Leap Motion topic 
 * and Publish SVH control message
 */

#include "ros/ros.h"
#include "tf/transform_datatypes.h"
#include <sensor_msgs/JointState.h>

#define PI 3.14159


int main(int argc, char **argv) {
    ros::init(argc, argv, "test_svh");
    ros::NodeHandle nh("~");
    /* SVH Command Publisher creation*/
    ros::Publisher svh_control_pub = nh.advertise<sensor_msgs::JointState>("channel_targets", 100);
   
    /*Initialized SVH command*/
    sensor_msgs::JointState hand_pos; 
    hand_pos.name.resize(9);
    hand_pos.position.resize(9);
    hand_pos.name[0] = "Index_Finger_Proximal";
    hand_pos.name[1] = "Index_Finger_Distal";
    hand_pos.name[2] = "Middle_Finger_Proximal";
    hand_pos.name[3] = "Middle_Finger_Distal";
    hand_pos.name[4] = "Ring_Finger";
    hand_pos.name[5] = "Pinky";
    hand_pos.name[6] = "Finger_Spread";
    hand_pos.name[7] = "Thumb_Flexion";
    hand_pos.name[8] = "Thumb_Opposition";
    
    hand_pos.header.stamp = ros::Time::now();
	
    std::cout<<"hand info receive"<<std::endl;
    /* select the firsthand*/
    for(int j = 0; j < 9 ;j++)
    {
     hand_pos.position[j] = 1;
    }
   
    /*Publish the new command*/
    svh_control_pub.publish(hand_pos);
    
    ros::spin();
    

    return 0;
}
