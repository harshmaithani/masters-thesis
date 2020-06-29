
/**********************************************************************************/

template <>
void Container<Eigen::VectorXd>::saveAsMFile()
{
   std::cout << "Writing M File for eigen" << std::endl ;
   
   std::ofstream mf( filename.c_str() ) ;
   if( mf.is_open() )
   {
      mf << "time = zeros(1, " << n << ") ;" << std::endl ; 
      mf << "data = zeros(" << objects[0].value.rows() << ", " << n << ") ;" << std::endl ; 
      
      for(int i=0; i<n; i++) 
      {
         TimestampedObject o = objects[i] ;
         mf << "data(:," << i+1 << ")=[" << o.value.transpose() << "].' ; " ;         
         mf << "time(" << i+1 << ")= " << o.time << " ;" << std::endl ;
      }
      
      mf.close() ; 
   }
}

