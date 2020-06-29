#ifndef _MTOOLS_MATHS_ROTATIONS_
#define _MTOOLS_MATHS_ROTATIONS_

#include <iostream>
#include <Eigen/Core>


namespace mtools_maths
{

/*************************************************************************************/

/**
* takes an angle (rad) and return ist corresponding values in range [0, 2*pi]
*/
inline double normalized_angle_positive(const double a) 
{
   return std::fmod( std::fmod(a, 2.*M_PI) + 2.*M_PI, 2.*M_PI ) ;
}


/*************************************************************************************/

/**
* takes an angle (rad) and return ist corresponding values in range [-pi, pi]
*/
inline double normalized_angle(const double a) 
{
   double r = normalized_angle_positive(a) ; 
   if( r > M_PI ) r -= 2.*M_PI ;
   
   return r ;
}

/*************************************************************************************/

inline double shortest_angular_distance(const double from, const double to) 
{
   double r = normalized_angle_positive( normalized_angle_positive(to) - normalized_angle_positive(from) ) ;
   if( r > M_PI ) r = -( 2.*M_PI - r ) ;
   return r ;
}

/*************************************************************************************/
/*************************************************************************************/

inline Eigen::Matrix3d e2R(const Eigen::Vector3d e) 
{

   double ph = e(0), th = e(1), ps = e(2) ; 
   double   sph = sin(ph), 
            cph = cos(ph),
            sth = sin(th),
            cth = cos(th),
            sps = sin(ps),
            cps = cos(ps) ;
            
   Eigen::Matrix3d R ; 
   R <<  cth*cps, -cph*sps+sph*sth*cps,  sph*sps+cph*sth*cps, 
         cth*sps,  cph*cps+sph*sth*sps, -sph*cps+cph*sth*sps,
        -sth,      sph*cth,              cph*cth ; 
   
   return R ;
}

/*************************************************************************************/

inline Eigen:: Vector3d R2e(const Eigen::Matrix3d R) 
{
   double phi, theta, psi ;
   phi   = normalized_angle( atan2( R(2,1), R(2,2) ) ) ;
   theta = normalized_angle( asin( -R(2,0) ) ) ;
   psi   = normalized_angle( atan2( R(1,0), R(0,0) ) ) ;
   
   Eigen::Vector3d e ; 
   e << phi, theta, psi ;
   return e ;
}



}

#endif
