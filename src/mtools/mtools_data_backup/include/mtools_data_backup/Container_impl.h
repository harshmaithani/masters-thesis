
/**********************************************************************************/

template <typename T> 
Container<T>::Container() : n(0)
{
}

/**********************************************************************************/

template <typename T>
Container<T>::~Container(){}


/**********************************************************************************/

template <typename T>
void Container<T>::setPath(const std::string p)
{
   filename = p ;
}

/**********************************************************************************/

template <typename T> 
void Container<T>::push_back(const double time, const T& value) 
{
   n++ ;
   static double time_initial = time ;

   TimestampedObject to ;      
   to.time = time - time_initial ;   
   to.value = value ;
   
   objects.push_back(to) ;  
}

/**********************************************************************************/

template <typename T> 
void Container<T>::push_back(const T& t) 
{
   n++ ;
   TimestampedObject in ;
   in.time = n ;
   in.value = t ;
   objects.push_back(in) ;   
}


/**********************************************************************************/

template <typename T>
std::string Container<T>::info() const
{
   std::stringstream ss ;
   ss << "Object type in container : " << typeid( objects[0].value ).name() << std::endl ;
   ss << "Number of objects : " << n ;
   
   return ss.str() ;
}

/**********************************************************************************/
template <typename T>
void Container<T>::saveAsMFile()
{
   std::cout << "This function is not impleted yet for '" << typeid( objects[0].value ).name() << "'." << std::endl ;
}

