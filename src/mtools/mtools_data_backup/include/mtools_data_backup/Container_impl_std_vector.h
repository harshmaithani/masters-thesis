
/**********************************************************************************/

template <>
void Container<std::vector<double> >::saveAsMFile()
{
   std::cout << "Writing M file for std::vector<double>..." << std::endl ;
   
   std::ofstream mf( filename.c_str() ) ;
   if( mf.is_open() )
   {
      mf << "time = zeros(1, " << n << ") ;" << std::endl ; 
      mf << "data = zeros(" << objects[0].value.size() << ", " << n << ") ;" << std::endl ; 
      
      for(int i=0; i<n; i++) 
      {
         TimestampedObject o = objects[i] ;
         mf << "data(:," << i+1 << ")=[" ; 
         for(int j=0; j<o.value.size(); j++) mf << o.value[j] << " " ; 
         mf << "].' ; " ;         
         mf << "time(" << i+1 << ")= " << o.time << " ;" << std::endl ;
      }
      
      mf.close() ; 
   }
}

