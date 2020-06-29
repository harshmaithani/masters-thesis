/* Leap motion bridge 
 * Subscribe to Ros Leap Motion topic 
 * and Publish SVH control message
 */

#include "ros/ros.h"
#include "tf/transform_datatypes.h"
#include <sensor_msgs/JointState.h>
#include "leap_client/HandInfoList.h"
#include "leap_client/HandInfo.h"
#include "leap_client/FingerInfo.h"
#include "leap_client/BoneInfo.h"

#define PI 3.14159
ros::Publisher svh_control_pub;
sensor_msgs::JointState hand_pos_prev; 

void leap_motion_callback(const leap_client::HandInfoList::ConstPtr& input)
{
  float Leap_pos[9];
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
    /* select the first hand*/
    
    leap_client::HandInfo hand = input->hands[0];
    
    /*Compute bone angle for the Thumb flexion*/
    leap_client::FingerInfo finger = hand.fingers[0];
    leap_client::BoneInfo bone[4];
    for (int j = 0 ; j < 4; j++){
	bone[j] = finger.bones[j];
    }
    hand_pos.position[7] = bone[2].angle; 
    /*Compute bone angles for index */
    finger = hand.fingers[1];
    for (int j = 0 ; j < 4; j++){
      bone[j] = finger.bones[j];
    }
    hand_pos.position[0] = bone[1].angle;

    hand_pos.position[1] = bone[2].angle * 1.2;

    
    /*Compute bone angles for middle */
    finger = hand.fingers[2];
    for (int j = 0 ; j < 4; j++){
      bone[j] = finger.bones[j];
    }
    hand_pos.position[2] = bone[1].angle;

    hand_pos.position[3] = bone[2].angle * 1.2;
    
    /*Compute bone angles for ring */
    finger = hand.fingers[3];
    for (int j = 0 ; j < 4; j++){
      bone[j] = finger.bones[j];
    }
    hand_pos.position[4] = bone[2].angle;
 
    /*Compute bone angles for pinky */
    finger = hand.fingers[4];
    for (int j = 0 ; j < 4; j++){
      bone[j] = finger.bones[j];
    }
    hand_pos.position[5] = bone[2].angle;
  
    /*Compute bone angles for finger spread */
    leap_client::FingerInfo finger1 = hand.fingers[1];
    leap_client::FingerInfo finger2 = hand.fingers[2];
    
    bone[0] = finger1.bones[1];
    bone[1] = finger2.bones[1];
    
    
    tf::Vector3 bone_hand = tf::Vector3(bone[0].direction.x,bone[0].direction.y,bone[0].direction.z);
    tf::Vector3 bone_proximal = tf::Vector3(bone[1].direction.x,bone[1].direction.y,bone[1].direction.z);
    
    float angle = tf::tfAngle(bone_hand,bone_proximal);

    hand_pos.position[6] = angle;

    /*Compute Thumb Opposition */  
    finger1 = hand.fingers[0];
    finger2 = hand.fingers[4];

    bone[0] = finger1.bones[1];
    bone[1] = finger2.bones[0];
   
    bone_hand = tf::Vector3(finger1.tip_position.x,finger1.tip_position.y,finger1.tip_position.z);
    bone_proximal = tf::Vector3(finger2.tip_position.x,finger2.tip_position.y,finger2.tip_position.z);

     hand_pos.position[8] = 0.99 - tf::tfDistance(bone_hand,bone_proximal) / 80;
    
    //hand_pos.position[8] = 0 ;
    
    float min_pos[9] = {0,0,0,0,0,0,0,0,0};
    float max_pos[9] = {0.8,1.33,0.8,1.33,0.98,0.98,0.58,0.97,0.99};
    
    /*Apply min max range for each position command*/
    for (int i = 0; i <9 ; i++){
      if(hand_pos.position[i] < min_pos[i]) hand_pos.position[i] = min_pos[i];
      if(hand_pos.position[i] > max_pos[i]) hand_pos.position[i] = max_pos[i];
    }
    
    /*Apply simple filter to limit little movement*/
    for (int i = 0 ; i < 9 ; i++){
      hand_pos.position[i] = (hand_pos_prev.position[i] + hand_pos.position[i]) / 2;
    }
    
    /*Publish the new command*/
    svh_control_pub.publish(hand_pos);
    hand_pos_prev = hand_pos;
}




int main(int argc, char **argv) {
    ros::init(argc, argv, "Leap_motion_bridge");
    ros::NodeHandle nh("~");
    hand_pos_prev.name.resize(9);
    hand_pos_prev.position.resize(9);
    for (int i = 0 ; i < 9 ; i++){
      hand_pos_prev.position[i] = 0;
    }
    
    /* SVH Command Publisher creation*/
    svh_control_pub = nh.advertise<sensor_msgs::JointState>("channel_targets", 100);
    
    /* Leap motion Listener creation*/
    ros::Subscriber leap_motion_sub = nh.subscribe("leap_client", 100, leap_motion_callback );
    
    ros::spin();
    

    return 0;
}
