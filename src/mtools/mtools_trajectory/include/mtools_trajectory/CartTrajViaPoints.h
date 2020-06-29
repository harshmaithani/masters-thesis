#ifndef _MTOOLS_TRAJECTORY_CARTTRAJVIAPOINTS_
#define _MTOOLS_TRAJECTORY_CARTTRAJVIAPOINTS_

#include <mtools_trajectory/JointTrajViaPoints.h>

namespace mtools_trajectory
{

class CartTrajViaPoints: public JointTrajViaPoints
{
   public:
   CartTrajViaPoints(const std::vector<Eigen::Matrix4d> &traj, const Eigen::VectorXd &kv, const Eigen::VectorXd &ka, const double cycle_time) ; 
   CartTrajViaPoints(const std::vector<Eigen::Matrix4d> &traj, const std::vector<double> &kv, const std::vector<double> &ka, const double cycle_time) ; 
   CartTrajViaPoints(){} ;
   ~CartTrajViaPoints(){} ;
         
   void init(const std::vector<Eigen::Matrix4d> &traj, const Eigen::VectorXd &kv, const Eigen::VectorXd &ka, const double cycle_time); 
   
   using JointTrajViaPoints::getNextState ; // unhiding of base class' getNextState overloads  
   void getNextState(Eigen::Matrix4d &T) ;
  
} ; // eof class def

} // eof namespace


#endif // header guard
