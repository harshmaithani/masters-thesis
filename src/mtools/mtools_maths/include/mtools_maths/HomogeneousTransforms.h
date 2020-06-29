#ifndef _MTOOLS_MATHS_HOMOGENEOUS_TRANSFORMS_
#define _MTOOLS_MATHS_HOMOGENEOUS_TRANSFORMS_

#include <Eigen/Core>

namespace mtools_maths
{
/*************************************************************************************/
/*************************************************************************************/

inline Eigen::Vector3d P(const Eigen::Matrix4d T) {return T.col(3).head(3) ;}
inline Eigen::Matrix3d R(const Eigen::Matrix4d T) {return T.topLeftCorner(3,3) ;}


/*************************************************************************************/
/*************************************************************************************/

inline double C(const double t) { return (fabs(t)==M_PI/2)?0:cos(t) ; }
inline double S(const double t) { return (fabs(t)==M_PI  )?0:sin(t) ; }

/*************************************************************************************/
/*************************************************************************************/

inline Eigen::Matrix4d RotX(const double t)
{
   double ct = C(t), st = S(t) ;    
   Eigen::Matrix4d T ; 
   T <<  1,  0,   0,   0, 
         0,  ct, -st,  0, 
         0,  st,  ct,  0, 
         0,  0,   0,   1 ;
         
   return T ;
}

/*************************************************************************************/

inline Eigen::Matrix4d RotY(const double t)
{
   double ct = C(t), st = S(t) ;    
   Eigen::Matrix4d T ; 
   T <<   ct,  0,  st, 0, 
          0,   1,  0,  0, 
         -st,  0,  ct, 0, 
          0,   0,  0,  1 ;
         
   return T ;
}

/*************************************************************************************/

inline Eigen::Matrix4d RotZ(const double t)
{
   double ct = C(t), st = S(t) ;    
   Eigen::Matrix4d T ; 
   T <<  ct, -st,  0,  0, 
         st,  ct,  0,  0, 
         0,   0,   1,  0, 
         0,   0,   0,  1 ;
         
   return T ;
}

/*************************************************************************************/
/*************************************************************************************/


} // eof namespace

#endif
