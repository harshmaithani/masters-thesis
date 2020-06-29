#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry> // cross prod
#include <mtools_maths/mtools_maths.h> // RotX

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <kuka_lwr4p_controllers/utils.h>
#include <kuka_lwr4p_controllers_msgs/RobotState.h>

#include <mtools_trajectory/CartTrajViaPoints.h>

#define N_DOF 7
#define TIMEOUT ros::Duration(5)
#define COUT(x) {std::cout << x << std::endl ;}

using namespace mtools_maths; 


int main(int argc, char** argv) 
{
   // ros: node init
   ros::init(argc, argv, "find_bracket") ;
   ros::NodeHandle nh ;
   ros::AsyncSpinner spinner(1) ;
   spinner.start() ;
            
   // workspace: set up where to search the bracket
   std::vector<double> bX(4,0.), bY(4,0.) ; // corners of the workspace wrt robot base B
   bX[0] = -.32442 ;    bY[0] = -.35975 ;
   bX[1] = -.43299 ;    bY[1] =  .22650 ;
   bX[2] = -.72672 ;    bY[2] =  .17598 ;
   bX[3] = -.62156 ;    bY[3] = -.41426 ;
   // altitudes of points are zeros (z0123=0), ws corners belong to the same plane as the robot base.   
   
   // workspace: find transform between robot base and workspace
   // z-axes are aligned, origin of the workspace is the first points, x-axis of ws points to 2nd point.   
   Eigen::Vector3d x, y, S, N, A, O ;
   O << bX[0], bY[0], 0 ;
   x << bX[1], bY[1], 0 ;
   y << bX[3], bY[3], 0 ;
   S = (x-O).normalized() ;
   N = (y-O).normalized() ;
   A = S.cross(N).normalized() ; // should be [0,0,1] 
   
   Eigen::Matrix4d bTws = Eigen::Matrix4d::Identity() ;
   bTws.col(0).head(3) = S ;
   bTws.col(1).head(3) = N ;
   bTws.col(2).head(3) = A ;
   bTws.col(3).head(3) = O ;
   
   COUT("bTws=[" << bTws << "];") ;   
   
   // traj for scan: find first pos of the sensor
   double height = .4 ; // height of the sensor when scanning
   Eigen::Matrix4d bTe_scan_start_pose = bTws ;
   bTe_scan_start_pose(2,3) = height ;
   bTe_scan_start_pose = bTe_scan_start_pose*RotX(M_PI)*RotZ(-M_PI/2) ;
   
   COUT("bTe1=[" << bTe_scan_start_pose << "]; ") ;       
   
   // traj for scan: set pass-by points
   std::vector<Eigen::Matrix4d> scan ;
   //scan.push_back( Eigen::Matrix4d::Identity() ) ;
   scan.push_back( Eigen::Matrix4d::Identity() ) ; scan.back().col(3).head(2) << .0, .6 ;
   scan.push_back( Eigen::Matrix4d::Identity() ) ; scan.back().col(3).head(2) << .1, .6 ;
   scan.push_back( Eigen::Matrix4d::Identity() ) ; scan.back().col(3).head(2) << .1, .0 ;
   scan.push_back( Eigen::Matrix4d::Identity() ) ; scan.back().col(3).head(2) << .2, .0 ;   
   scan.push_back( Eigen::Matrix4d::Identity() ) ; scan.back().col(3).head(2) << .2, .6 ;      
   scan.push_back( Eigen::Matrix4d::Identity() ) ; scan.back().col(3).head(2) << .3, .6 ;      
   scan.push_back( Eigen::Matrix4d::Identity() ) ; scan.back().col(3).head(2) << .3, .0 ;         
   scan.push_back( Eigen::Matrix4d::Identity() ) ;
   for(int i=0; i<scan.size(); i++) scan[i] = bTe_scan_start_pose*scan[i] ;
   for(int i=0; i<scan.size(); i++) COUT("scan(:,:," << i+1 <<") = [" << scan[i] << "]; ") ;
         
   // kuka: wait for robot states msg
   kuka_lwr4p_controllers_msgs::RobotStateConstPtr rs = 
      ros::topic::waitForMessage<kuka_lwr4p_controllers_msgs::RobotState>("/kuka_lwr4p/robot_states", TIMEOUT) ;
   if( rs==NULL )
   {
      ROS_ERROR("Could not get the robot state, robot_state_controller is not publishing.") ;
      ros::shutdown() ;
      return -1 ;
   }   
   Eigen::Matrix4d bTe = 
      kuka_lwr4p_controllers::FRICartPose2HomogeneousTransform(rs->cart_pose_msr) ;
      
   COUT("bTe=[" << bTe << "];") ;   
    
   // kuka: wait for controller manager
   if( !kuka_lwr4p_controllers::WaitForControllerManager(TIMEOUT) ) 
   {
      ROS_ERROR("Controllers are not available. Make sure you started the KUKA LWR4+ Hardware Interface node.") ;
      ros::shutdown() ;
      return -1 ;
   }
               
   // kuka: move to start pose for scan
   std::vector<Eigen::Matrix4d> traj ;
   std::vector<double> kv(6), ka(6), stiffness(6, 2000), damping(6,.7), effort(6,0.) ;
   kv[0] = kv[1] = kv[2] = .1 ; kv[3] = kv[4] = kv[5] = .1 ;
   ka[0] = ka[1] = ka[2] = 1. ; ka[3] = ka[4] = ka[5] = 1. ;
   stiffness[3] = stiffness[4] = stiffness[5] = 200 ;
   traj.push_back(bTe) ; 
   traj.push_back(bTe_scan_start_pose) ;
   
   for(int i=0; i<scan.size(); i++) traj.push_back(scan[i]) ;
   
   kuka_lwr4p_controllers::CartTrajectoryGoal g ;  
   kuka_lwr4p_controllers::PrepareCartTrajectoryGoal(g, traj, kv, ka, effort, stiffness, damping) ;  
   
   kuka_lwr4p_controllers::LoadController("cart_impedance_controller") ;
   kuka_lwr4p_controllers::StartController("cart_impedance_controller") ;   
   
   actionlib::SimpleActionClient<
      kuka_lwr4p_controllers::CartTrajectoryAction> ac("/kuka_lwr4p/fri_node", false) ;     
   ac.waitForServer() ;      
   ac.sendGoal(g) ;
   bool traj_ended = ac.waitForResult(ros::Duration(120)) ;   
   if( traj_ended )
   {
      actionlib::SimpleClientGoalState state = ac.getState();
      ROS_INFO("Traj ended, status: %s",state.toString().c_str());
   }
   else
   {
      ROS_ERROR("Robot could not reach the start pos for scanning.") ; 
      ros::shutdown() ;
      return -1 ;
   }      
   
   kuka_lwr4p_controllers::StopController("cart_impedance_controller") ; 
   kuka_lwr4p_controllers::UnloadController("cart_impedance_controller") ;    
      
   ros::shutdown() ;
   return 0 ;
   
}
