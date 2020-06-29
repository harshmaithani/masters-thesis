#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry> // cross prod
#include <mtools_maths/mtools_maths.h> // RotX

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/PointCloud.h>

#include <kuka_lwr4p_controllers/utils.h>
#include <kuka_lwr4p_controllers_msgs/RobotState.h>

#define N_DOF 7
#define TIMEOUT ros::Duration(5)
#define COUT(x) {std::cout << x << std::endl ;}

using namespace mtools_maths; 

ros::Publisher js_pub ;
sensor_msgs::JointState js_msg ;

ros::Publisher nx_pub ;

void RobotStateCallback(const kuka_lwr4p_controllers_msgs::RobotState::ConstPtr &msg) 
{
   // cart pose broadcaster
   static tf::TransformBroadcaster br; 
   tf::Transform tr ;
   Eigen::Matrix4d tr_h = 
      kuka_lwr4p_controllers::FRICartPose2HomogeneousTransform(msg->cart_pose_msr) ;
   Eigen::Vector3d rpy = R2e( tr_h.topLeftCorner(3,3) ) ;
   tf::Quaternion q ; 
   q.setRPY( rpy(0), rpy(1), rpy(2) ) ; 
   
   tr.setOrigin( tf::Vector3(tr_h(0,3), tr_h(1,3), tr_h(2,3)) ) ; 
   tr.setRotation(q) ;
   br.sendTransform( tf::StampedTransform(tr, ros::Time::now(), "world", "cart_pose_msr")) ;      
   
   // joint states
   js_msg.position = msg->joint_pos_msr ;
   js_msg.header.stamp = ros::Time::now() ;
   js_pub.publish(js_msg) ;
   
}

void EnsensoCallback(const sensor_msgs::PointCloud::Ptr &msg)
{
   msg->header.frame_id = "/ensenso_nx" ;
   msg->header.stamp = ros::Time::now() ;
   nx_pub.publish(*msg) ;
}


int main(int argc, char** argv) 
{
   // ros: node init
   ros::init(argc, argv, "find_bracket_replay") ;
   ros::NodeHandle nh ;
   ros::AsyncSpinner spinner(1) ;
   spinner.start() ;
   
   ros::Subscriber rs_sub = nh.subscribe("/kuka_lwr4p/robot_states", 5, RobotStateCallback) ;
   js_pub = nh.advertise<sensor_msgs::JointState>("/kuka_lwr4p/joint_states_msr", 0) ;
   js_msg.name.push_back("A1_joint") ;
   js_msg.name.push_back("A2_joint") ;
   js_msg.name.push_back("E1_joint") ;
   js_msg.name.push_back("A3_joint") ;
   js_msg.name.push_back("A4_joint") ;
   js_msg.name.push_back("A5_joint") ;
   js_msg.name.push_back("A6_joint") ;
   js_msg.velocity = std::vector<double>(7, 0.) ; 
   js_msg.effort = std::vector<double>(7, 0.) ;
   
   ros::Subscriber nx_sub = nh.subscribe("/ensenso_nx/pointcloud", 10, EnsensoCallback) ; 
   nx_pub = nh.advertise<sensor_msgs::PointCloud>("/ensenso_nx/pointcloud_2", 10) ;
   
   while( ros::ok() ) ; 
   ros::shutdown() ;             
   return 0 ;
   
}
