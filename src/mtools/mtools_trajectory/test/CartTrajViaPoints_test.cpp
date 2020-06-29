#include <mtools_trajectory/CartTrajViaPoints.h>

#include <mtools_maths/mtools_maths.h>
#include <mtools_data_backup/Container.h>

#include <Eigen/Core>

//#define COUT(x) {std::cout << x << std::endl ;}

int main(int argc, char** argv) 
{

   COUT("Tester: init kv, ka...") ;
   double time_end = 15 ;
   double time_step = 0.01 ;
   double time = -time_step ; 
   
   Eigen::VectorXd kv(6), ka(6) ;
   kv(0) = kv(1) = kv(2) = .25 ; // m/s
   kv(3) = kv(4) = kv(5) = 1. ;  // rad/s     
   ka(0) = ka(1) = ka(2) = 2 ;  // m/s2
   ka(3) = ka(4) = ka(5) = 5 ;  // rad/s2     
   COUT("Tester: kv= " << kv.transpose() << ", ka=" << ka.transpose()) ;
      
   COUT("Tester: fill traj...") ;
        
   Eigen::Matrix4d p1 = mtools_maths::RotX(M_PI) ;
   Eigen::Matrix4d p2 = mtools_maths::RotX(-M_PI) ; p2.col(3) << .3, 0., .5, 1. ;
   
   std::vector<Eigen::Matrix4d> poses ;
   poses.push_back( Eigen::Matrix4d::Identity() ) ;
   poses.push_back( p1 ) ;
   poses.push_back( p2 ) ;
   poses.push_back( Eigen::Matrix4d::Identity() ) ;      
      
   COUT("Tester: init traj object...") ;
   mtools_trajectory::CartTrajViaPoints traj(poses, kv, ka, time_step) ;
            
   COUT("Tester: Entering main loop...") ;            
   Eigen::VectorXd p(7), pd(7), pdd(7) ;
   mtools_data_backup::Container<Eigen::VectorXd> data_p, data_pd, data_pdd ;   
   
   while( !traj.isDone() ) 
   {
      // increments time
      time += time_step ;
      //COUT("Tester: time=" << time) ;
            
      // update joint profiles
      traj.getNextState(p, pd, pdd) ;
          
      // backup
      data_p.push_back(   time, p   ) ;
      data_pd.push_back(  time, pd  ) ;
      data_pdd.push_back( time, pdd ) ;          
   } 
         
   COUT("data_p container's info: " << data_p.info() ) ;
      
   data_p.setPath("/home/sylvain/Documents/Fichiers_ROS/groovy_catkin_workspace/src/mtools/mtools_trajectory/test/CartTrajViaPoints_test_q.m") ; 
   data_pd.setPath("/home/sylvain/Documents/Fichiers_ROS/groovy_catkin_workspace/src/mtools/mtools_trajectory/test/CartTrajViaPoints_test_qd.m") ;
   data_pdd.setPath("/home/sylvain/Documents/Fichiers_ROS/groovy_catkin_workspace/src/mtools/mtools_trajectory/test/CartTrajViaPoints_test_qdd.m") ;

   data_p.saveAsMFile() ;
   data_pd.saveAsMFile() ;
   data_pdd.saveAsMFile() ;

   return 0 ;
}
