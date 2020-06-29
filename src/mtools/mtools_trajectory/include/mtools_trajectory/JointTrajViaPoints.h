#ifndef _MTOOLS_TRAJECTORY_JOINTTRAJVIAPOINTS_
#define _MTOOLS_TRAJECTORY_JOINTTRAJVIAPOINTS_

#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Core>
#include <mtools_maths/mtools_maths.h>

#ifndef COUT
#define COUT(x) {std::cout << x << std::endl ;}
#endif

namespace mtools_trajectory
{

class JointTrajViaPoints
{

   public:   
   JointTrajViaPoints(const Eigen::MatrixXd &traj, const Eigen::VectorXd &kv, const Eigen::VectorXd &ka, const double cycle_time, const std::vector<bool> joint_types=std::vector<bool>()) ; 
   JointTrajViaPoints(const std::vector< std::vector<double> > &traj, const std::vector<double> &kv, const std::vector<double> &ka, const double cycle_time, const std::vector<bool> joint_types=std::vector<bool>()) ; 
   JointTrajViaPoints(){} ;
   ~JointTrajViaPoints(){} ;
   
   void init(const Eigen::MatrixXd &traj, const Eigen::VectorXd &kv, const Eigen::VectorXd &ka, const double cycle_time, const std::vector<bool> joint_types=std::vector<bool>() ) ;
   
   void getNextState(Eigen::VectorXd &q, Eigen::VectorXd &qd, Eigen::VectorXd &qdd) ;
   void getNextState(std::vector<double> &q) ;      

   void setCycleTime(const double dt) { cycle_time_ = dt ;}
   bool isDone() const { return done_ ;}
   
   private:
   
   void update(const double time, Eigen::VectorXd &q, Eigen::VectorXd &qd, Eigen::VectorXd &qdd) ; 
   
   // robot param
   int n_dof_ ;   
   Eigen::VectorXd kv_ ; // maximum velocities per joints
   Eigen::VectorXd ka_ ; // maximum accelerations per joints
   std::vector<bool> joint_types_ ; // false if revolute joint, true if prismatic
  
   // traj param
   int n_pts_ ;            // number of points
   Eigen::MatrixXd q_ ;    // trajectory to follow in joint space, col <=> points
   Eigen::MatrixXd qd_ ;   // velocities in joint space
   Eigen::MatrixXd D_ ;    // distances between points
   Eigen::MatrixXd lambda_ ; // velocities synchronization vector between joints
   Eigen::MatrixXd nu_ ;   // velocities synchronization vector between joints
   Eigen::VectorXd h_ ;    // time between to points, per joints
   Eigen::VectorXd T_ ;    // blend time around points, per joints 
   Eigen::VectorXd t_ ;    // wall time over the trajectory
   
   // online 
   int current_point_  ;
   double cycle_time_ ;
   double time_ ;
   bool done_ ;
   
} ; // eof class def

template <typename T> int sign(T val) { return (T(0) < val) - (val < T(0)); }

} // eof namespace


#endif // header guard
