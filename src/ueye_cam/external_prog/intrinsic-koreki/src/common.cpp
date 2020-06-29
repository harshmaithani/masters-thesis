/** 
 * \file common.cpp
 *
 * \brief <b>Implementation file for method use for single and stereo camera calibration </b>. 
 *
 * \details The file provides common functions such as points research, 
 * class constructor, pattern's definition, etc...
 * \n
 * \date September 2013
 *
 * \version 1.1
 *
 * \author XK\n
 * \n
 * IRCCYN\n
 * Equipe Robotique\n
 * 1, rue de la Noe\n
 * BP 92101\n
 * 44321 NANTES Cedex\n
 * FRANCE\n
 * \n
 * http://www.irccyn.ec-nantes.fr
 *
*/
#include "calibrage.h"
#include "Chessboard.h"
 
/**
 * calibrage
 * @fn calibrage::calibrage()
 * @brief class calibrage constructor
 * @details This method must be use in first. It initializes main variables 
 *\n
*/
calibrage::calibrage(std::string name, std::vector<std::string> imageFilenames_1, bool click, bool save, std::string cameraType, bool useOpenCV)
{
   /* data path */
   repertoire_calibtab = "./../data/calibrationtables/";
   repertoire_extrinsic = "./../data/extrinsic/";
   repertoire_intrinsic = "./../data/intrinsic/";
        
   /* variables */    
   m_imageFilenames_1 = imageFilenames_1;
   m_nimages = imageFilenames_1.size();        
   m_click = click;     
   m_useOpenCV = useOpenCV; 
   m_save = save;
   m_camera = name;

   /* don't touch */  
   iter = 0;
   niter = 0;
   nbImgCal = 0; 
   for(int i=0;i<1000;i++) validImage[i] = 0; 


   /* Parameters for Baumer */
   double pixelSizeBaumer = 3.75; // µm
   /* Parameters for imperX */
   double pixelSizeImperX = 3.75; // µm
   /* Parameters for marlin */
   double pixelSizeMarlin = 6.7; // µm
   
   /* Focal lens */
   double lensNormal = 3.5; // mm
   double lensWide = 1.4; // mm

   /* Intrinsic estimation */
   if(cameraType == "fisheye")
      Focal = lensWide/pixelSizeImperX*1000;   
   else if(cameraType == "pinhole")
      Focal = lensNormal/pixelSizeBaumer*1000;   
}


calibrage::calibrage(std::string namel, std::string namer, std::vector<std::string> imageFilenames_1, std::vector<std::string> imageFilenames_2, bool click, bool save, std::string cameraType, bool useOpenCV)
{
   /* data path */
   repertoire_calibtab = "./../data/calibrationtables/";
   repertoire_extrinsic = "./../data/extrinsic/";
   repertoire_intrinsic = "./../data/intrinsic/";
        
   /* variables */    
   m_imageFilenames_1 = imageFilenames_1;
   m_imageFilenames_2 = imageFilenames_2;
   m_nimages = imageFilenames_1.size();        
   m_click = click;    
   m_useOpenCV = useOpenCV;   
   m_save = save;
   m_camera_left = namel;
   m_camera_right = namer;

   /* don't touch */  
   iter = 0;;
   niter = 0;
   nbImgCal = 0; 
   for(int i=0;i<1000;i++) validImage[i] = 0; 


   /* Parameters for Baumer */
   double pixelSizeBaumer = 3.75; // µm
   /* Parameters for imperX */
   double pixelSizeImperX = 3.75; // µm
   /* Parameters for marlin */
   double pixelSizeMarlin = 6.7; // µm
   
   /* Focal lens */
   double lensNormal = 3.5; // mm
   double lensWide = 1.4; // mm

   /* Intrinsic estimation */
   if(cameraType == "fisheye")
      Focal = lensWide/pixelSizeImperX*1000;   
   else if(cameraType == "pinhole")
      Focal = lensNormal/pixelSizeBaumer*1000;   
}

/**
 * ~calibrage
 * @fn calibrage::~calibrage()
 * @brief class calibrage destructor
 *\n
*/
calibrage::~calibrage()
{
}

/**
 * readPattern
 * @fn bool calibrage::readPattern(const string &cfgfile)
 * @brief Load the grid configuration file
 * @details This method load the configuration file,
 * check if data is valid and set global variables.
 *\n
 * @param cfgfile
 * @return true if OK
*/
bool calibrage::readPattern(const string &cfgfile) 
{
   // reading configuration file
   vpIoTools::loadConfigFile(cfgfile);
   vpIoTools::readConfigVar("BoardSize_Width:", boardSize.width);
   vpIoTools::readConfigVar("BoardSize_Height:", boardSize.height);
   vpIoTools::readConfigVar("BoardSize_Depth:", boardSizedepth);
   vpIoTools::readConfigVar("Square_Size_X:", squareSize_X);
   vpIoTools::readConfigVar("Square_Size_Y:", squareSize_Y);
   vpIoTools::readConfigVar("Square_Size_Z:", squareSize_Z);
   vpIoTools::readConfigVar("Bias:", BIAS);
   vpIoTools::readConfigVar("Calibrate_Pattern:", patternToUse);

   cout << "\ngrid width : " << boardSize.width << endl;
   cout << "grid height: " << boardSize.height << endl;
   if (!patternToUse.compare("GRID2D")) 
      currentTestPattern.type = GRID2D; 
   if (!patternToUse.compare("DOT2D")) 
      currentTestPattern.type = DOT2D;
   if (!patternToUse.compare("DOT3D")) 
   {
      cout << "grid depth : " << boardSizedepth << endl;
      cout << "Bias: " << BIAS << endl;
      cout << "Square Size Z: " << squareSize_Z << endl;
      currentTestPattern.type = DOT3D;
   }

   cout << "Square Size X: " << squareSize_X << endl;
   cout << "Square Size Y: " << squareSize_Y << endl;
   cout << "pattern : " << patternToUse << endl;

   if (boardSize.width <= 0 || boardSize.height <= 0)
   { 
      cerr << "Invalid Board size: " << boardSize.width << " " << endl;
      return false;
   }
   if (squareSize_X <= 10e-6 || squareSize_Y <= 10e-6) 
   { 
      cerr << "Invalid square size " << squareSize_X << " " << squareSize_Y << endl;
      return false;
   }
   return true;
}

/**
 * defPattern
 * @fn void calibrage::defPattern(const string &cfgfile)
 * @brief set the grid of the pattern
 * @details Load the pattern with readPattern() and set the grid of the pattern.
 * 2 patterns are available : DOT2D / GRID2D
 * Other function is useful : setPatternParam in calibrage.h
 *\n
 * @param cfgfile 
 * @return true if OK
*/
bool calibrage::defPattern(const string &cfgfile)
{
   vector<vpPoint> grid; grid.clear();
   vector<vpPoint> gridToTrack; gridToTrack.clear();

   if(!readPattern(cfgfile))
      return false;

   switch(currentTestPattern.type) 
   {
      case DOT2D:
      {
         setPatternParam(&currentTestPattern,boardSize.width,boardSize.height,squareSize_X,squareSize_Y);
         for(int i=0;i<currentTestPattern.nbX;i++)
            for(int j=0;j<currentTestPattern.nbY;j++)
               grid.push_back(create_vpPoint(i*currentTestPattern.dx,j*currentTestPattern.dy,0));

//         //if there is a grid to track:
//         gridToTrack.push_back( create_vpPoint(  currentTestPattern.dx,  currentTestPattern.dy,0));
//         gridToTrack.push_back( create_vpPoint(  currentTestPattern.dx,4*currentTestPattern.dy,0));
//         gridToTrack.push_back( create_vpPoint(3*currentTestPattern.dx,4*currentTestPattern.dy,0));
//         gridToTrack.push_back( create_vpPoint(4*currentTestPattern.dx,  currentTestPattern.dy,0));
//         setPatternParam(&currentTestPattern,grid,gridToTrack);

         setPatternParam(&currentTestPattern,grid);
         break;
      }
      case GRID2D:
      {
         setPatternParam(&currentTestPattern,boardSize.width,boardSize.height,squareSize_X,squareSize_Y);
         for(int i=0;i<currentTestPattern.nbX;i++)
            for(int j=0;j<currentTestPattern.nbY;j++)
               grid.push_back(create_vpPoint(i*currentTestPattern.dx,j*currentTestPattern.dy,0));
                
         setPatternParam(&currentTestPattern,grid);
         break;
      }
      case DOT3D:
      {
         setPatternParam(&currentTestPattern,boardSize.width,boardSize.height,boardSizedepth,squareSize_X,squareSize_Y,squareSize_Z,BIAS);
         float dx = currentTestPattern.dx, dy = currentTestPattern.dy, dz = currentTestPattern.dz;
         float delta = currentTestPattern.bias;
         grid.push_back( create_vpPoint(delta,0,delta));
         grid.push_back( create_vpPoint(delta,0,delta + dz));
         grid.push_back( create_vpPoint(delta + dx,0,delta + dz));
         grid.push_back( create_vpPoint(delta + dx,0,delta));

         grid.push_back( create_vpPoint(0,delta,delta));
         grid.push_back( create_vpPoint(0,delta + dy,delta));
         grid.push_back( create_vpPoint(0,delta + dy,delta + dz));
         grid.push_back( create_vpPoint(0,delta,delta + dz));

         grid.push_back( create_vpPoint(delta,delta,0));
         grid.push_back( create_vpPoint(delta + dx,delta,0));
         grid.push_back( create_vpPoint(delta + dx,delta + dy,0));
         grid.push_back( create_vpPoint(delta,delta + dy,0));

         setPatternParam(&currentTestPattern,grid);
         break;
      }
   }
   return true;
}

/**
 * displayPoints
 * @fn void calibrage::displayPoints(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsTotal, string name)
 * @brief Display the pt list image point
 * @details This method display the image points list "pt" from the "image"
 * names "name". pt is set with findImagePoints() method
 *\n
 * @param image, pt, nbPointsTotal, name
*/
void calibrage::displayPoints(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsTotal, string name)
{  
   char comment[FILENAME_MAX];
   vpDisplay::display(image);
   int kolor=1;

   for(int i=0; i<nbPointsTotal; i++)
   {
      sprintf(comment,"%d",i+1 );
      if(i>0)
      {
         if(i%boardSize.height == 0)
            kolor+=2;
         vpDisplay::displayLine(image,pt[i],pt[i-1],vpColor::allColors[kolor],1);
      }
      vpDisplay::displayCircle(image,pt[i],5,vpColor::allColors[kolor],true,2);
      vpDisplay::displayCharString(image,pt[i],&comment[0],vpColor::red);
   }
   vpDisplay::displayCharString(image, image.getHeight() -15, 10,name.c_str(),vpColor::orange);
   vpDisplay::displayCharString(image, 15, 10,"A left click to validate this pose.",vpColor::red);
   vpDisplay::displayCharString(image, 30, 10,"A right click to retry.",vpColor::red);
   vpDisplay::displayCharString(image, 45, 10,"A middle click to don't care of this pose.",vpColor::red);

   vpDisplay::flush(image) ;
}

/***********************************************************************************************
# 
#                                    Points search
# 
************************************************************************************************/

/**
 * findImagePoints
 * @fn int calibrage::findImagePoints(vpImage<unsigned char> &image, vpImagePoint pt[], string name)
 * @brief find all the image's points and save it in the image's points list pt
 * @details This method find all image's points from 
 * the "image" names "name" and save it in pt
 *\n
 * @param image, pt, name
 * @return true if all points are found, false in other case 
*/
bool calibrage::findImagePoints(vpImage<unsigned char> &image, vpImagePoint pt[], string name)
{
   switch(currentTestPattern.type)
   {
      case DOT2D :
      {
         /* Try to find the grid - automatic mode */
         if(!findDotAuto(image, pt))
         {
            /* else - Manual mode for all point */
            if(!findDots(image, pt,currentTestPattern.nbPoints,name)) 
               return false;
         }
         break;
      }
      case GRID2D:
      {
         /* Try to find the grid - automatic mode */
         if(!findGridAuto(image, pt))
         {
            /* else - Manual mode for all point */
            if(!findCross(image, pt,currentTestPattern.nbPoints,name))
               return false;   
         }
         break;
      }
      case DOT3D:
      {

            /* else - Manual mode for all point */
            if(!findDots(image, pt,currentTestPattern.nbPoints,name))
               return false;   

         break;
      }
   }
   return true;
}

/**
 * findSubCorner
 * @fn void calibrage::findSubCorner(vpImage<unsigned char> &image, vpImagePoint *pt, int Size)
 * @brief finds the nearest cross in the image 
 * @details This function modifies the coordinates of vpImagePoint pt.
 * This function is for the CHESSBOARD grid
 *\n
 * @param image, pt, Size
*/
void calibrage::findSubCorner(vpImage<unsigned char> &image, vpImagePoint *pt, int size)
{
   Mat img;
   vector<Point2f> pts;
   vpImageConvert::convert(image, img);
   pts.push_back( Point2f(pt->get_u(),pt->get_v()));
   cornerSubPix(img,pts,Size(size,size), Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
   pt->set_uv( pts[0].x , pts[0].y );
}

/**
 * findGridAuto
 * @fn bool calibrage::findGridAuto(vpImage<unsigned char> &image, vpImagePoint pt[])
 * @brief fills the vpImagePoint "pt" tab with positions of all crosses in the image.
 * @details fills the vpImagePoint "pt" tab with positions of all crosses in the image.
 * Call 'findChessboardCorners' function, an OpenCV function.
 * This function is for the CHESSBOARD grid
 *\n
 * @param image, pt
 * @return false if failed, true else
*/
bool calibrage::findGridAuto(vpImage<unsigned char> &image, vpImagePoint pt[])
{
   Mat img; 
   Size size(currentTestPattern.nbY,currentTestPattern.nbX); //Nb_columns * Nb_lines
   vpImageConvert::convert(image, img);
   vector<Point2f> tmp;
   int flags = CV_CALIB_CB_ADAPTIVE_THRESH + CV_CALIB_CB_NORMALIZE_IMAGE + CV_CALIB_CB_FILTER_QUADS + CV_CALIB_CB_FAST_CHECK;

   if(m_useOpenCV)
   {
      if(!findChessboardCorners(img, size, tmp))
         return false;

      cornerSubPix(img,tmp,Size(11,11), Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
   }
   else
   {
      Chessboard* chess = new Chessboard(size,img);

      chess->findCorners();

      if(!chess->cornersFound())
         return false;
 
      tmp = chess->getCorners();

      delete chess;
   }

   for(int i=0;i<(int)tmp.size();i++)
      pt[i].set_uv(tmp[i].x,tmp[i].y);
   
   return true;
}

/**
 * findDotAuto
 * @fn bool calibrage::findDotAuto(vpImage<unsigned char> &image, vpImagePoint pt[])
 * @brief fills the vpImagePoint "pt" tab with positions of all dots in the image.
 * @details fills the vpImagePoint "pt" tab with positions of all crosses in the image.
 * This function is for the CIRCLES_GRID grid
 *\n
 * @param image, pt
 * @return false if failed, true else
*/
bool calibrage::findDotAuto(vpImage<unsigned char> &image, vpImagePoint pt[])
{
   Mat img;
   Size size(currentTestPattern.nbY,currentTestPattern.nbX); //Nb_columns * Nb_lines
   vpImageConvert::convert(image, img);
   vector<Point2f> tmp;

   if(!findCirclesGrid(img, size, tmp))
      return false;
    
   for(int i=0;i<(int)tmp.size();i++)
      pt[i].set_uv(tmp[i].x,tmp[i].y);
   
   return true;
}

/**
 * findDots
 * @fn bool calibrage::findDots(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsToTrack)
 * @brief fills the vpImagePoint pt tab with nbPointsToTrack vpImagePoint
 * @details This function track a Dot in the image around a one manual click.
 * pt[] contains all center of gravity (cog) of the dots.
 * This function is for the CIRCLES_GRID grid
 *\n
 * @param image, pt, nbPointsToTrack
 * @return false, if the user interrupts the tracking by wheel-click or left+rigth click, return true else
*/
bool calibrage::findDots(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsToTrack, string name)
{
   vpDot2 d[nbPointsToTrack];
   vpMouseButton::vpMouseButtonType button;
   vpImagePoint point;
   char comment[FILENAME_MAX]; 

   for(int i=0;i<nbPointsToTrack;)
   {
      vpDisplay::display(image);
      for(int j=0; j<i; j++)
      {
         d[j].display(image,vpColor::red);
         sprintf(comment,"%d",j+1 );
         vpDisplay::displayCharString(image,d[j].getCog(), &comment[0], vpColor::green);
      }
      sprintf(comment,"Click in the dot %d / %d",i+1,nbPointsToTrack );
      vpDisplay::displayCharString(image, image.getHeight() -15, 10,name.c_str(),vpColor::orange);
      vpDisplay::displayCharString(image,10,10, &comment[0], vpColor::red);
      vpDisplay::displayCharString(image,20,10,"Right click to Cancel last point",vpColor::red);
      vpDisplay::displayCharString(image,30,10,"Middle Click to ignore the image",vpColor::red);
      vpDisplay::flush(image);
      vpDisplay::getClick(image,point,button);

      switch(button)
      {
         case vpMouseButton::button1:
            d[i].setGrayLevelPrecision(0.85);
            try{ d[i].initTracking(image,point); } 
            catch(...) {i--;}
            i++;
            break;
         case vpMouseButton::button2: 
            cout << "   Middle click -> image ignored" << endl;
            iter++;
            niter++;  
            return false;
         case vpMouseButton::button3:   
            if(i>=1) 
               i--;
            break;
      }
      if(i==nbPointsToTrack)
      {
         vpDisplay::display(image);
         for(int j=0; j<i; j++)
         {
            d[j].display(image,vpColor::red);
            pt[j] = d[j].getCog();
            sprintf(comment,"%d",j+1 );
            vpDisplay::displayCharString(image,pt[j],&comment[0],vpColor::green);
         }
         vpDisplay::displayCharString(image,10,10,"Left click to Valid",vpColor::red);
         vpDisplay::displayCharString(image, image.getHeight() -15, 10,name.c_str(),vpColor::orange);
         vpDisplay::displayCharString(image,20,10,"Right click to Cancel last point",vpColor::red);
         vpDisplay::flush(image);
         vpDisplay::getClick(image,point,button);
         if(button == vpMouseButton::button3) 
            i--;
      }
   }
   return true;
}

/**
 * findCross
 * @fn bool calibrage::findCross(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsToTrack)
 * @brief fills the vpImagePoint pt tab with nbPointsToTrack vpImagePoint in the image
 * @details This function get the position of a click on the image, and by calling 'findSubCorner' function find the nearest cross on a grid
 * This function is for the CHESSBOARD grid
 *\n
 * @param image, pt, nbPointsToTrack
 * @return false, if the user interrupts the tracking by wheel-click or left+rigth click, return true else
*/
bool calibrage::findCross(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsToTrack, string name)
{
   vpMouseButton::vpMouseButtonType button;
   vpImagePoint point;
   char comment[FILENAME_MAX]; 

   for(int i=0;i<nbPointsToTrack;)
   {
      vpDisplay::display(image);
      for(int j=0; j<i; j++)
      {
         vpDisplay::displayCross(image,pt[j],8,vpColor::orange,2);
         sprintf(comment,"%d",j+1 );
         vpDisplay::displayCharString(image,pt[j], &comment[0], vpColor::green);
      }
      sprintf(comment,"Click in the dot %d / %d",i+1 , nbPointsToTrack);
      vpDisplay::displayCharString(image, image.getHeight() -15, 10,name.c_str(),vpColor::orange);
      vpDisplay::displayCharString(image,10,10, &comment[0], vpColor::red);
      vpDisplay::displayCharString(image,20,10,"Right click to Cancel last point",vpColor::red);
      vpDisplay::displayCharString(image,30,10,"Middle click to ignore the image",vpColor::red);
      vpDisplay::flush(image);
      vpDisplay::getClick(image,point,button);

      switch(button)
      {
         case vpMouseButton::button1:
            findSubCorner(image, &point,11);
            pt[i] = point;
            i++;
            break;
         case vpMouseButton::button2: 
            cout << "   Middle click -> image ignored" << endl;
            iter++;
            niter++;
            cout<<endl;
            return false;
         case vpMouseButton::button3:
            if(i>=1) 
               i--; 
            break;
      }
      if(i==nbPointsToTrack)
      {
         cout<<endl;   
         vpDisplay::display(image);
         for(int j=0; j<i; j++)
         {
            vpDisplay::displayCross(image,pt[j],8,vpColor::orange,2);
            sprintf(comment,"%d",j+1 );
            vpDisplay::displayCharString(image,pt[j],&comment[0],vpColor::green);
         }
         vpDisplay::displayCharString(image,10,10,"Left click to Valid",vpColor::red);
         vpDisplay::displayCharString(image, image.getHeight() -15, 10,name.c_str(),vpColor::orange);
         vpDisplay::displayCharString(image,20,10,"Right click to Cancel last point",vpColor::red);
         vpDisplay::flush(image);
         vpDisplay::getClick(image,point,button);
         if(button == vpMouseButton::button3) 
            i--;
      }
   }
   return true;
}

/**
* computeRetroprojectionError
 * @fn float calibrage::computeRetroprojectionError(vector<vpImagePoint>list1, vector<vpImagePoint>list2, int begin, int end)
 * @brief Compute the sum of the distance between the points of the 2 lists
 * @details The sum begin at the item 0 and stop at the last item of list except if 'begin' or 'end' are passed
 *\n
 * @param list1, list2, begin, end
 * @return -1 if the lists size are different, retroprojection error if no error
*/
float calibrage::computeRetroprojectionError(vector<vpImagePoint>list1, vector<vpImagePoint>list2, int begin, int end)
{
   if(end==0)
      end = list1.size();
   if(begin>=end)
      begin = 0;
   int nbPointsTotal = currentTestPattern.nbPoints;
   float err;
   if(list1.size() == list2.size())
   {
      float totalErr = 0;
      for(int i=begin; i<end; i++)
      {
         err = vpImagePoint::sqrDistance(list1.at(i),list2.at(i));
         totalErr += err;//*err;
      }
      int nbPointsTotal = end-begin;
      return sqrt(totalErr/nbPointsTotal);
   }
   else
   {
      cout << "Not the same number of points" << "List 1:"<< list1.size() << " | List 2:" << list2.size() <<endl;
      return -1;
   }
}

/**
* loadCalibTab
 * @fn bool calibrage::loadCalibTab(string name, vpImagePoint pt[])
 * @brief load saved calibration tables
 * @details this method load the calibration tab for the image "name if exist.
 * It stores the result in a new list points pt
 *\n
 * @param name, pt
 * @return true if the file exist, false else
*/
bool calibrage::loadCalibTab(string name, vpImagePoint pt[])
{
   ifstream loadFile;
   string line;
   float x,y,z,u,v;
   int nbPointsTotal=currentTestPattern.nbPoints;
   int i=0;
   loadFile.open (name.c_str(), ifstream::in); 
   if(loadFile.good()) 
   {     
      getline (loadFile,line);
      while ( loadFile.good() && i<nbPointsTotal)
      {
         getline (loadFile,line);
         stringstream ss(line);
         //cout.precision(13);
         ss >> x >> y >> z >> u >> v;
         pt[i].set_u(u);
         pt[i].set_v(v);
         i++;
      }   
      loadFile.close();
      return true;
   }
   else
      return false;
}
