#include <mtools_trajectory/CartTrajViaPoints.h>

namespace mtools_trajectory
{

/**********************************************************************************/
/**********************************************************************************/

CartTrajViaPoints::CartTrajViaPoints(const std::vector<Eigen::Matrix4d> &traj, const Eigen::VectorXd &kv, const Eigen::VectorXd &ka, const double cycle_time)
{  
   init(traj, kv, ka, cycle_time) ;
   
   //--------------------Added by Harsh 12-5-2015-----------------//
   std::cout<<"Size of traj in CartTrajViaPoints 1 is "<<traj.size()<<std::endl;
   std::cout<<"Trajectory in CartTrajViaPoints 1 is"<<std::endl;
   for (int harsh=0;harsh<traj.size();harsh++)
    {
      std::cout<<traj[harsh]<<std::endl;
     }
   //
}

/**********************************************************************************/

CartTrajViaPoints::CartTrajViaPoints(const std::vector<Eigen::Matrix4d> &traj, const std::vector<double> &kv, const std::vector<double> &ka, const double cycle_time)
{
   int n_dof = kv.size() ;
   Eigen::VectorXd vel(n_dof), acc(n_dof) ;
   for(int i=0 ; i<n_dof; i++)
   {
      vel(i) = kv[i] ;
      acc(i) = ka[i] ;
   }
      
   init(traj, vel, acc, cycle_time) ;
   
 //--------------------Added by Harsh 12-5-2015-----------------//
   std::cout<<"Size of traj in CartTrajViaPoints 2 is "<<traj.size()<<std::endl;
   std::cout<<"Trajectory in CartTrajViaPoints 2 is"<<std::endl;
   for (int harsh=0;harsh<traj.size();harsh++)
    {
      std::cout<<traj[harsh]<<std::endl;
     }
   
   //
   
}

/**********************************************************************************/
/**********************************************************************************/

void CartTrajViaPoints::init(const std::vector<Eigen::Matrix4d> &traj, const Eigen::VectorXd &kv, const Eigen::VectorXd &ka, const double cycle_time)
{
   // Transform 4x4 homogeneous transform into 6-dof vector [x y z phi theta psi]^T
   Eigen::MatrixXd p_traj(6, traj.size()) ; // traj as a list of homogeneous transform
   for(int k=0; k<traj.size(); k++)
   {
     p_traj.col(k).head(3) = mtools_maths::P( traj[k] )  ; 
     p_traj.col(k).tail(3) = mtools_maths::R2e( mtools_maths::R(traj[k]) ) ;
   }

   // Tell to JointTraj gen that the first three joints are prismatics
   std::vector<bool> joint_types(6, false) ;
   joint_types[0] = joint_types[1] = joint_types[2] = true ; // first 3 joints are prismatic

   // Initialize the object through superclass init method
   JointTrajViaPoints::init(p_traj, kv, ka, cycle_time, joint_types) ;

   // Done ^^
   
   //--------------------Added by Harsh 12-5-2015-----------------//
   std::cout<<"Size of traj in CartTrajViaPoints 3 is "<<traj.size()<<std::endl;
   std::cout<<"Trajectory in CartTrajViaPoints 3 is"<<std::endl;
   for (int harsh=0;harsh<traj.size();harsh++)
    {
      std::cout<<traj[harsh]<<std::endl;
     }
   
   //
   
  
}


/**********************************************************************************/
/**********************************************************************************/

void CartTrajViaPoints::getNextState(Eigen::Matrix4d &T)
{
   // init
   T = Eigen::Matrix4d::Identity() ;
   
   // get the next state of the trajectory
   Eigen::VectorXd p(6), pd(6), pdd(6) ;
   JointTrajViaPoints::getNextState(p, pd, pdd) ;
   
   // fill the homogeneous transformation
   T.topLeftCorner(3, 3) = mtools_maths::e2R( p.tail(3) ) ; 
   T.col(3).head(3) = p.head(3) ;
   
   
}

} //eof namespace
