/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/** 
 * Simple stand-alone ROS node that takes data from NetFT sensor and
 * Publishes it ROS topic
 */

#include <ros/ros.h>
#include "netft_rdt_driver/netft_rdt_driver.h"
#include <geometry_msgs/WrenchStamped.h>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <diagnostic_updater/DiagnosticStatusWrapper.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;


int main(int argc, char **argv)
{ 
  ros::init(argc, argv, "netft_node");
  ros::NodeHandle nh, nh_private("~");
  
  // Get parameters from the server
  double publish_rate;
  string ip_address, sensor_name, frame_id;
  nh_private.param(std::string("ip_address"), ip_address, std::string("192.168.0.20"));
  nh_private.param(std::string("sensor_name"), sensor_name, std::string("netft"));
  nh_private.param(std::string("frame_id"), frame_id, std::string("base_link"));
  nh_private.param(std::string("publish_rate"), publish_rate, 100.0);
  if (!nh_private.hasParam("ip_address"))
    ROS_WARN_STREAM("Parameter [~ip_address] not found, using default: " << ip_address);
  if (!nh_private.hasParam("sensor_name"))
    ROS_WARN_STREAM("Parameter [~sensor_name] not found, using default: " << sensor_name );
  if (!nh_private.hasParam("frame_id"))
    ROS_WARN_STREAM("Parameter [~frame_id] not found, using default: " << frame_id );
  if (!nh_private.hasParam("publish_rate"))
    ROS_WARN_STREAM("Parameter [~publish_rate] not found, using default: " << publish_rate << " Hz");

  std::auto_ptr<netft_rdt_driver::NetFTRDTDriver> netft(new netft_rdt_driver::NetFTRDTDriver(ip_address));
  
  // Setup publishers
  ros::Publisher pub;
  pub = nh.advertise<geometry_msgs::WrenchStamped>(sensor_name + "/data", 100);
  ros::Rate pub_rate(publish_rate);
  geometry_msgs::WrenchStamped data;

  ros::Duration diag_pub_duration(1.0);
  ros::Publisher diag_pub = nh.advertise<diagnostic_msgs::DiagnosticArray>(sensor_name + "/diagnostics", 2);
  diagnostic_msgs::DiagnosticArray diag_array;
  diag_array.status.reserve(1);
  diagnostic_updater::DiagnosticStatusWrapper diag_status;
  ros::Time last_diag_pub_time(ros::Time::now());

  while (ros::ok())
  {
    if (netft->waitForNewData())
    {
      netft->getData(data);
      data.header.frame_id = frame_id;
      pub.publish(data);
    }
    
    ros::Time current_time(ros::Time::now());
    if ( (current_time - last_diag_pub_time) > diag_pub_duration )
    {
      diag_array.status.clear();
      netft->diagnostics(diag_status);
      diag_array.status.push_back(diag_status);
      diag_array.header.stamp = ros::Time::now();
      diag_pub.publish(diag_array);
      last_diag_pub_time = current_time;
    }
    
    ros::spinOnce();
    pub_rate.sleep();
  }
  
  return 0;
}
