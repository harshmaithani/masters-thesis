#include "ros/ros.h"
#include <sensor_msgs/JointState.h>

float hand_pos_input[10][9]; 
int count;
void leap_motion_bridge_callback(const sensor_msgs::JointState & input)
{
  for (int i = 0 ; i < 9 ; i++)
  {
    hand_pos_input[count][i] = input.position[i]; 
  }
  if (count < 9) count++;
  else count = 0;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "Filter");
    ros::NodeHandle nh("~");
    
    ros::Rate loop_rate(20);
    count = 0;
    /* SVH Command Publisher creation*/
    ros::Publisher svh_control_pub = nh.advertise<sensor_msgs::JointState>("channel_targets", 100);
    
    /* Leap motion Listener creation*/
    ros::Subscriber leap_motion_bridge_sub = nh.subscribe("leap_bridge", 100, leap_motion_bridge_callback );
    
    
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
    
    while(ros::ok()){
        hand_pos.header.stamp = ros::Time::now();
	for(int i = 0 ; i < 9; i++){
	  hand_pos.position[i] = 0;
	  for(int j = 0 ; j < 10; j++){
	    hand_pos.position[i] = hand_pos.position[i]+hand_pos_input[j][i];
	  }
	  hand_pos.position[i] = hand_pos.position[i] / 10;
	}
	svh_control_pub.publish(hand_pos);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}