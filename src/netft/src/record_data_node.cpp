/*	!!!!!!!! CHANGE
	This test node stores in a .bag file the pose of the ROS turtle.	
	In order to convert the .bag file into a .csv file
   	it is necessary to type in the terminal the following command:
	
	rostopic echo -p -b test.bag -a >> <name_of_the_file>.csv 

	Note that if you want to store x, y and theta
	in different files it is possible to type the three different commands:

	rostopic echo -p -b test.bag /x >> <name_of_the_file_x>.csv
	rostopic echo -p -b test.bag /y >> <name_of_the_file_y>.csv
	rostopic echo -p -b test.bag /theta >> <name_of_the_file_theta>.csv
*/

//ROS

#include <ros/ros.h>
#include "netft_rdt_driver/netft_rdt_driver.h"
#include <geometry_msgs/WrenchStamped.h>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <diagnostic_updater/DiagnosticStatusWrapper.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <boost/program_options.hpp>

#include "netft_rdt_driver/netft_rdt_driver.h"
#include <stdint.h>
#include <exception>

#include "ros/ros.h"
#include <rosbag/bag.h>

//ROS msgs
#include <std_msgs/Float64.h>
#include <geometry_msgs/WrenchStamped.h>

rosbag::Bag ftmeasures;

void recordCallback(geometry_msgs::WrenchStamped netft_data){
	
	std_msgs::Float64 fx;
	std_msgs::Float64 fy;
	std_msgs::Float64 fz;
	std_msgs::Float64 tx;
	std_msgs::Float64 ty;
	std_msgs::Float64 tz;

    	fx.data = netft_data.wrench.force.x;
	fy.data = netft_data.wrench.force.y;
	fz.data = netft_data.wrench.force.z;
	tx.data = netft_data.wrench.torque.x;
	ty.data = netft_data.wrench.torque.y;
	tz.data = netft_data.wrench.torque.z;

    	ftmeasures.write("fx", ros::Time::now(), fx);
    	ftmeasures.write("fy", ros::Time::now(), fy);
	ftmeasures.write("fz", ros::Time::now(), fz);
    	ftmeasures.write("tx", ros::Time::now(), tx);
    	ftmeasures.write("ty", ros::Time::now(), ty);
	ftmeasures.write("tz", ros::Time::now(), tz);
	
	ROS_INFO("I am in callback");
	//ROS_INFO("fx %f",fx.data);	
	
}

int main (int argc, char** argv)
{
	//ROS Initialization
	ros::init(argc, argv, "record_data_node");
	ROS_INFO("Connected !!!!!");
	ros::NodeHandle nh_("~"); //ROS Handler - local namespace.
        
	ftmeasures.open("test.bag", rosbag::bagmode::Write);

	//Subscribing
	ROS_INFO("Subscribing to topics\n");
	ros::Subscriber sub = nh_.subscribe<geometry_msgs::WrenchStamped> ("/netft/data", 1, recordCallback);

	ros::Rate rate(100);
	ROS_INFO("SPINNING @ 100Hz");
	while (ros::ok()){
		ros::spinOnce();		
		rate.sleep();
	} 

        ftmeasures.close(); 

	ROS_INFO("ROS-Node Terminated\n");
}
