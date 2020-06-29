#include <mtools_trajectory/JointTrajViaPoints.h>

namespace mtools_trajectory
{

/**********************************************************************************/

JointTrajViaPoints::JointTrajViaPoints(const Eigen::MatrixXd &traj, 
                                       const Eigen::VectorXd &kv, 
                                       const Eigen::VectorXd &ka, 
                                       const double cycle_time, 
                                       const std::vector<bool> joint_types )
{
   init(traj, kv, ka, cycle_time, joint_types) ;
}

/**********************************************************************************/

JointTrajViaPoints::JointTrajViaPoints(const std::vector<std::vector<double> > &traj, 
                                       const std::vector<double> &kv, 
                                       const std::vector<double> &ka, 
                                       const double cycle_time, 
                                       const std::vector<bool> joint_types )
{   
   // traj as a list of points !   
   int n_pts = traj.size() ; 
   int n_dof = traj[0].size() ;
   
   Eigen::MatrixXd t(n_dof, n_pts) ;
   Eigen::VectorXd v(n_dof), a(n_dof) ;
   
   for(int k=0; k<n_pts; k++) 
      for(int j=0; j<n_dof; j++) t(j,k) = traj[k][j] ;
      
   for(int j=0; j<n_dof; j++) v(j) = kv[j], a(j) = ka[j] ;
   
   init(t, v, a, cycle_time, joint_types) ;
}

/**********************************************************************************/

void JointTrajViaPoints::init(const Eigen::MatrixXd &traj, 
                              const Eigen::VectorXd &kv, 
                              const Eigen::VectorXd &ka, 
                              const double cycle_time, 
                              const std::vector<bool> joint_types )
{

   //DBG COUT("JointTrajViaPoints::init call !"  << this) ;
   
   // instanciation of attributes
   n_dof_ = traj.rows() ;
   n_pts_ = traj.cols() ;
            
   q_  = Eigen::MatrixXd(n_dof_, n_pts_) ;   
   kv_ = Eigen::VectorXd(n_dof_) ;
   ka_ = Eigen::VectorXd(n_dof_) ;
   D_  = Eigen::MatrixXd(n_dof_, n_pts_) ;   
   lambda_ = Eigen::MatrixXd(n_dof_, n_pts_) ;
   nu_ = Eigen::MatrixXd(n_dof_, n_pts_) ;
   qd_ = Eigen::MatrixXd(n_dof_, n_pts_) ;
   h_  = Eigen::VectorXd(n_pts_-1) ;
   T_  = Eigen::VectorXd(n_pts_) ;
   t_  = Eigen::VectorXd(n_pts_) ;
   
   if( joint_types.empty() ) joint_types_ = std::vector<bool>(n_dof_, false) ; // joints are revolute by default
   else joint_types_ = joint_types ;
   
   q_  = traj ;
   kv_ = kv  ; 
   ka_ = ka  ;
   
   current_point_ = 0 ; 
   time_ = -1 ;
   cycle_time_ = cycle_time ;
   done_ = false ;
   
   //DBG COUT("Got traj=\n" << q_ ) ;
   //DBG COUT("Got n_dof=" << n_dof_ << ", n_pts_=" << n_pts_ ) ;
   //DBG COUT("Got kv=" << kv_.transpose() << ", ka=" << ka_.transpose() ) ;
      
   //DBG COUT("JointTrajViaPoints: init synchro vars") ;
   // synchronisation variable initialization
   for(int k=0; k<n_pts_-1; k++) 
   {
      // distances init
      for(int j=0; j<n_dof_; j++) 
      {
         if( !joint_types_[j] ) // if revolute joint
            D_(j,k) = mtools_maths::shortest_angular_distance( q_(j,k), q_(j,k+1) ) ;
         else
            D_(j,k) = q_(j,k+1) - q_(j,k) ; 
      }
      
      // synchro
      for(int j=0; j<n_dof_; j++)
      {
         lambda_(j,k) = 1 ;
         nu_(j,k) = 1 ;
         for(int i=0; i<n_dof_; i++)
         {
            lambda_(j,k) = std::min( lambda_(j,k), kv_(i)*fabs(D_(j,k))/kv_(j)/fabs(D_(i,k)) ) ; 
            nu_(j,k) =     std::min( nu_(j,k),     ka_(i)*fabs(D_(j,k))/ka_(j)/fabs(D_(i,k)) ) ;
         }
         
         qd_(j,k) = lambda_(j,k)*kv_(j)*sign(D_(j,k)) ;
      }
   }
   
   //DBG COUT("D=\n" << D_) ; 
   //DBG COUT("lambda=\n" << lambda_) ; 
   //DBG COUT("nu=\n" << nu_) ; 
   //DBG COUT("qd=\n" << qd_) ; 
   

   // timing vars
   //DBG COUT("JointTrajViaPoints: init timing vars") ;
   Eigen::MatrixXd h(n_dof_, n_pts_-1), T(n_dof_, n_pts_) ;
   for(int k=0; k<n_pts_; k++) 
   {      
      for(int j=0; j<n_dof_; j++)
      {
         if( k<n_pts_-1 ) 
         {
            if( qd_(j,k)!=0 ) h(j,k) = D_(j,k)/qd_(j,k) ; // FIXME manage qd==0 !  
            else h(j,k) = -1 ;
         }
         
         if( k==0 || k==n_pts_-1 ) 
         {
            if( nu_(j)!=0 ) T(j,k) = lambda_(j)*kv_(j)/nu_(j)/ka_(j)*3/4 ; // time 1st/last blend
            else T(j,k) = -1 ;
         }
         else 
            T(j,k) = fabs( qd_(j,k)-qd_(j,k-1) )/ka_(j)*3/4 ;
      }                  
   }   
   
   //DBG COUT("T(j,k)=\n" << T) ; 
   //DBG COUT("h(j,k)=\n" << h) ; 
   
   // construct wall time
   //DBG COUT("JointTrajViaPoints: construct wall time") ;
   T_ = T.colwise().maxCoeff() ;
   h_ = h.colwise().maxCoeff() ;
   t_(0) = 0 ;
   for(int k=1; k<n_pts_; k++) t_(k) = T_(0) - T_(k) + h_.head(k).sum() ;

   //DBG COUT("Tk=\n" << T_.transpose()) ; 
   //DBG COUT("hk=\n" << h_.transpose()) ; 
   //DBG COUT("t=\n" << t_.transpose()) ;          
}



/**********************************************************************************/

void JointTrajViaPoints::update(const double time, Eigen::VectorXd &q, Eigen::VectorXd &qd, Eigen::VectorXd &qdd)
{
   int k = current_point_ ;
   
   // track current point
   if( current_point_ < n_pts_-1 )
   {
      if( time_ >= t_(k+1) )
      {           
         current_point_++ ;
         k=current_point_ ;        
         //DBG COUT("Point reached, going to next point " << current_point_ << ", time=" << time_ << "(" << time << ")") ;
      }
   }
      
   if( k==0 ) // first point
   {
      if( time_ <= 2*T_(k) ) // first blend at start
      {
         q   = q_.col(k) -qd_.col(k)/( 16*pow(T_(k),3) ) *pow(time_-t_(k),3) *(time_-t_(k)-4*T_(k)) ; //+ (time-t_(k)-T_(k))*0 ;
         qd  = qd_.col(k) *-1/4/pow(T_(k),3) *pow(time_-t_(k),2) *(time_-t_(k)-3*T_(k)) ;
         qdd = qd_.col(k) *-3/4/pow(T_(k),3) *(time_-t_(k))      *(time_-t_(k)-2*T_(k))  ;
      }
      else // linear traj, going to next point
      {
         q   = qd_.col(k) *(time_-t_(k)-T_(k)) +q_.col(k) ; 
         qd  = qd_.col(k) ;
         qdd = Eigen::VectorXd::Zero(n_dof_) ;
      }
      return ; 
   }
   
   if( k==n_pts_-1 ) // last point
   {    
      q   = q_.col(k)    -qd_.col(k-1) *-1/16/pow(T_(k),3) *pow(time_-t_(k),3) *(time_-t_(k)-4*T_(k)) + qd_.col(k-1)*(time_-t_(k)-T_(k)) ;
      qd  = qd_.col(k-1) -qd_.col(k-1) *-1/4/pow(T_(k),3)  *pow(time_-t_(k),2) *(time_-t_(k)-3*T_(k)) ;
      qdd =              -qd_.col(k-1) *-3/4/pow(T_(k),3)  *(time_-t_(k))      *(time_-t_(k)-2*T_(k)) ;
      
      if( time_ > t_(k) + 2*T_(k) ) done_ = true ;
      
      return ;
   }
   
   // when arriving there, it should not be k==0 nor k==n_pts_
   // intermediate points
   if( time_<=t_(k)+2*T_(k) ) // blend around k^th point
   {
      q   = q_.col(k)    +(qd_.col(k)-qd_.col(k-1)) *-1/16/pow(T_(k),3) *pow(time_-t_(k),3) *(time_-t_(k)-4*T_(k)) + qd_.col(k-1)*(time_-t_(k)-T_(k)) ;
      qd  = qd_.col(k-1) +(qd_.col(k)-qd_.col(k-1)) *-1/4/pow(T_(k),3)  *pow(time_-t_(k),2) *(time_-t_(k)-3*T_(k)) ;
      qdd =               (qd_.col(k)-qd_.col(k-1)) *-3/4/pow(T_(k),3)  *(time_-t_(k))      *(time_-t_(k)-2*T_(k)) ;
   }           
   else // linear traj, going to next point
   {
      q   = qd_.col(k) *(time_-t_(k)-T_(k)) +q_.col(k) ; 
      qd  = qd_.col(k) ;
      qdd = Eigen::VectorXd::Zero(n_dof_) ;
   }   

}

/**********************************************************************************/

void JointTrajViaPoints::getNextState(Eigen::VectorXd &q, Eigen::VectorXd &qd, Eigen::VectorXd &qdd)
{
   if(time_ < 0) time_ = 0 ;
   else time_ += cycle_time_ ;

   update(time_, q, qd, qdd) ;
}

/**********************************************************************************/

void JointTrajViaPoints::getNextState(std::vector<double> &q)
{
   Eigen::VectorXd   qq(n_dof_), qd(n_dof_), qdd(n_dof_) ; 
   
   if(time_ < 0) time_ = 0 ;
   else time_ += cycle_time_ ;

   update(time_, qq, qd, qdd) ;

   for(int i=0; i<n_dof_; i++) q[i] = qq(i) ;   
}

} //eof namespace
