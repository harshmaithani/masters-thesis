#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry> // cross prod
#include <mtools_maths/mtools_maths.h> // RotX

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/JointState.h>
#include <geometry_msgs/WrenchStamped.h>


#include <kuka_lwr4p_controllers/utils.h>
#include <kuka_lwr4p_controllers_msgs/RobotState.h>

#define N_DOF 7
#define TIMEOUT ros::Duration(5)
#define COUT(x) {std::cout << x << std::endl ;}

using namespace mtools_maths; 

ros::Publisher msr_pub, cmd_pub, eff_pub ;
sensor_msgs::JointState msr_msg, cmd_msg ;
geometry_msgs::WrenchStamped eff_msg ;

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
   
   // cart pose cmd br 
   tr_h = kuka_lwr4p_controllers::FRICartPose2HomogeneousTransform(msg->cart_pose_cmd) ;
   rpy = R2e( tr_h.topLeftCorner(3,3) ) ;  
   q.setRPY( rpy(0), rpy(1), rpy(2) ) ; 
   
   tr.setOrigin( tf::Vector3(tr_h(0,3), tr_h(1,3), tr_h(2,3)) ) ; 
   tr.setRotation(q) ;
   br.sendTransform( tf::StampedTransform(tr, ros::Time::now(), "world", "cart_pose_cmd")) ;      
   
   // joint states msr
   msr_msg.position = msg->joint_pos_msr ;
   msr_msg.header.stamp = ros::Time::now() ;
   msr_pub.publish(msr_msg) ;
   
   // joint states cmd
   cmd_msg.position = msg->joint_pos_cmd ;
   cmd_msg.header.stamp = ros::Time::now() ;
   cmd_pub.publish(cmd_msg) ;
   
   // end effector effort
   eff_msg.header.stamp = ros::Time::now() ;
   eff_msg.wrench.force.x = msg->cart_external_frc_trq_est[0] ;
   eff_msg.wrench.force.y = -msg->cart_external_frc_trq_est[1] ;
   eff_msg.wrench.force.z = msg->cart_external_frc_trq_est[2] ;
   eff_msg.wrench.torque.z = msg->cart_external_frc_trq_est[3] ;
   eff_msg.wrench.torque.y = msg->cart_external_frc_trq_est[4] ;
   eff_msg.wrench.torque.x = msg->cart_external_frc_trq_est[5] ;
   eff_pub.publish(eff_msg) ;
   
   
}

int main(int argc, char** argv) 
{
   // ros: node init
   ros::init(argc, argv, "kuka_cart_imp_replay") ;
   ros::NodeHandle nh ;
   ros::AsyncSpinner spinner(1) ;
   spinner.start() ; 
   
   std::vector<std::string> joint_names = {"A1_joint", "A2_joint", "E1_joint", "A3_joint", "A4_joint", "A5_joint", "A6_joint" } ; 
   
   msr_msg.name = cmd_msg.name = joint_names ;
   msr_msg.velocity = cmd_msg.velocity = std::vector<double>(7, 0.)  ;
   msr_msg.effort = cmd_msg.effort = std::vector<double>(7, 0.)  ; 
   eff_msg.header.frame_id = "/cart_pose_msr" ;  
         
   msr_pub = nh.advertise<sensor_msgs::JointState>("/kuka_lwr4p/joint_states_msr", 10) ;
   cmd_pub = nh.advertise<sensor_msgs::JointState>("/kuka_lwr4p/joint_states_cmd", 10) ;
   eff_pub = nh.advertise<geometry_msgs::WrenchStamped>("/kuka_lwr4p/ee_effort", 10) ;
   
   ros::Subscriber rs_sub = nh.subscribe("/kuka_lwr4p/robot_states", 5, RobotStateCallback) ; 
   
   while( ros::ok() ) ; 
   ros::shutdown() ;             
   return 0 ;
   
}
