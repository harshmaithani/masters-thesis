#ifndef _MTOOLS_DATA_BACKUP_CONTAINER_
#define _MTOOLS_DATA_BACKUP_CONTAINER_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include <Eigen/Core>

namespace mtools_data_backup {

template <typename T> 
class Container
{

   public:   
   Container() ;   
   ~Container() ; 
   
   struct TimestampedObject
   {
      double time ;
      T value ;
      T upper_limit ;
      T lower_limit ;
   };

   
   void push_back(const T&) ;
   void push_back(const double time, const T&) ;
   
   std::string info() const ;

   void saveAsMFile() ;
   
   void setPath(const std::string p) ;
	
	private:
		
	int n ;	
	std::vector<int> dim ;
	std::vector<TimestampedObject> objects ;		
	
	std::string filename ;
	
};

#include <mtools_data_backup/Container_impl.h>
#include <mtools_data_backup/Container_impl_eigen_vector.h>
#include <mtools_data_backup/Container_impl_std_vector.h>

} // namespace

#endif
