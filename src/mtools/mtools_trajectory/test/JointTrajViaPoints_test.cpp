#include <mtools_trajectory/JointTrajViaPoints.h>
#include <mtools_data_backup/Container.h>

#include <Eigen/Core>

//#define COUT(x) {std::cout << x << std::endl ;}

int main(int argc, char** argv) 
{

   COUT("Tester: init kv, ka...") ;
   double time_end = 15 ;
   double time_step = 0.001 ;
   double time = -time_step ; 
   
   Eigen::VectorXd kv = Eigen::VectorXd::Ones(7) ;
   Eigen::VectorXd ka = Eigen::VectorXd::Ones(7) ;
   kv = kv*.25 ; 
   ka = ka*5 ;  
   COUT("Tester: kv= " << kv.transpose() << ", ka=" << ka.transpose()) ;
      
   COUT("Tester: fill traj...") ;
   Eigen::MatrixXd q_traj(7, 5) ;
   q_traj.col(0) = Eigen::VectorXd::Zero(7) ;
   q_traj.col(1) <<       0, -M_PI/2,      0, M_PI/2,      0,       0,      0 ;
   q_traj.col(2) <<  M_PI/4, -M_PI/2,      0, M_PI/2,      0,       0,      0 ;
   q_traj.col(3) << -M_PI/4, -M_PI/2, M_PI/2, M_PI/2, M_PI/4, -M_PI/4, M_PI/4 ;
   q_traj.col(4) = Eigen::VectorXd::Zero(7) ;
   COUT("Tester: q_desired=\n" << q_traj ) ;
   
   COUT("Tester: init traj object...") ;
   mtools_trajectory::JointTrajViaPoints traj(q_traj, kv, ka, time_step) ;
   
   
   COUT("Tester: Entering main loop...") ;      
   
   Eigen::VectorXd q(7), qd(7), qdd(7) ;
   mtools_data_backup::Container<Eigen::VectorXd> data_q, data_qd, data_qdd ;   
   

   while( !traj.isDone() ) 
   {
      // increments time
      time += time_step ;
      COUT("Tester: time=" << time) ;
            
      // update joint profiles
      traj.getNextState(q, qd, qdd) ;
          
      // backup
      data_q.push_back(   time, q   ) ;
      data_qd.push_back(  time, qd  ) ;
      data_qdd.push_back( time, qdd ) ;          
   } 
   
   mtools_trajectory::JointTrajViaPoints traj2(q_traj, kv, ka, time_step) ;
   mtools_data_backup::Container<std::vector<double> > data_q2 ;
   time = -time_step ;
   while( !traj2.isDone() ) 
   {
      // increments time
      time += time_step ;
      //COUT("Tester: time=" << time) ;
      
      std::vector<double> q2(7, 0.) ;
      
      // update joint profiles      
      traj2.getNextState(q2) ;
          
      // backup      
      data_q2.push_back(  time, q2   ) ;      
   } 
   
   COUT("data_q container's info: " << data_q.info() ) ;
   
   data_q.setPath("/home/sylvain/Documents/Fichiers Matlab/traj_compare/JointTrajViaPoints_test/data_q.m") ;
   data_q2.setPath("/home/sylvain/Documents/Fichiers Matlab/traj_compare/JointTrajViaPoints_test/data_q2.m") ;
   //data_qd.setPath("/home/sylvain/Documents/Fichiers_ROS/groovy_catkin_workspace/src/mtools/mtools_trajectory/src/JointTrajViaPoints_test_qd.m") ;
   //data_qdd.setPath("/home/sylvain/Documents/Fichiers_ROS/groovy_catkin_workspace/src/mtools/mtools_trajectory/src/JointTrajViaPoints_test_qdd.m") ;

   data_q.saveAsMFile() ;
   data_q2.saveAsMFile() ;
   //data_qd.saveAsMFile() ;
   //data_qdd.saveAsMFile() ;

   return 0 ;
}
