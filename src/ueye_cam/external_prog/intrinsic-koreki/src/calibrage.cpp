/** 
 * \file calibrage.cpp
 *
 * \brief <b>Implementation file for method to Calibrate single camera</b>. 
 *
 * \details The class calibrage provides a basic interface to calibrate single
 *  and stereo camera
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

/**
* loadImage
 * @fn bool calibrage::loadImage(vpImage<unsigned char> image)
 * @brief load a PGM image file
 * @details This method load the image file name "opt_ppath" and number "iter". 
 * "opt_ppath" and "iter" are set in init() method. 
 * If "opt_video" is true, this method calls recordImageSequence() method and set "m_nimages" instead.
 *\n
 * @param gray image
 * @return TRUE, if the first image is loaded
*/
bool calibrage::loadImage(vpImage<unsigned char> image)
{
   filename = m_imageFilenames_1.at(iter);
   // Read the PGM image named "filename" on the disk, and put the
   // bitmap into the image structure I.  I is initialized to the
   // correct size
   // exception readPGM may throw various exception if, for example,
   // the file does not exist, or if the memory cannot be allocated
   try
   {
      vpImageIo::read(image, filename) ;
   }
   catch(...)
   {
      // an exception is throwned if an exception from readPGM has been catched
      // here this will result in the end of the program
      // Note that another error message has been printed from readPGM
      // to give more information about the error
      cerr << endl
      << "ERROR:" << endl;
      cerr << "  Cannot read " << filename << endl;
      return(-1);
   }
   return true;
}

/**
 * computeCalibrationViSP
 * @fn int calibrage::computeCalibrationViSP(vpCalibration::vpCalibrationMethodType methode)
 * @brief computes the ViSP calibration using a specific method
 * @details This method performs a calibration using ViSP. 
 * 2 methodes available : calibration without distortion and calibration with it.
 * "save" is set in init() method. 
 * If "save" is true, calibration data are save in ".txt" files for each image and intrinsic camera parameters are write in a ".xml" file
 *\n
 * @param methode
 * @return 0 if the computation was managed succeed.
*/
int calibrage::computeCalibrationViSP(vpCalibration::vpCalibrationMethodType methode)
{ 
   int result = vpCalibration::computeCalibrationMulti(methode,m_nimages,table_cal,cam,false);

   if(methode == vpCalibration::CALIB_VIRTUAL_VS)
   {
      if(result != 0)
         cout << "Calibration without distortion failed." << endl;
   }
   else if (methode == vpCalibration::CALIB_VIRTUAL_VS_DIST)
   {
      if(result != 0)
         cout << "Calibration with distortion failed." << endl;
   }

   if(m_save == true)
   {
      // write camera Parameters in a xml file
      vpXmlParserCamera xml;
      if(result == 0 && methode == vpCalibration::CALIB_VIRTUAL_VS)
      { 
         filename = repertoire_intrinsic + "visp_calibrage.xml";
         remove(filename.c_str());
         int resultSaving = xml.save(cam, filename.c_str(), "Camera", imageViSP.getWidth(), imageViSP.getHeight());
         if(resultSaving != vpXmlParserCamera::SEQUENCE_OK)
            cout << "Failed to save the camera parameters without distortion in visp_calibrage.xml" << endl;
      }
      if(result == 0 && methode == vpCalibration::CALIB_VIRTUAL_VS_DIST) 
      {
         filename = repertoire_intrinsic + "visp_calibrage_dist.xml";
         remove(filename.c_str());
         int resultSavingDist =  xml.save(cam, filename.c_str(), "Camera", imageViSP.getWidth(), imageViSP.getHeight());
         if(resultSavingDist != vpXmlParserCamera::SEQUENCE_OK )
            cout << "Failed to save the camera parameters with distortion in visp_calibrage_dist.xml" << endl;
      }
      vpXmlParser::cleanup();
   }
   return result;
}

/**
 * computeOpenCV
 * @fn float calibrage::computeOpenCV(int nbImages, int width, int height)
 * @brief computes the calibration using OpenCV 
 * @details This function needs the number of images used 'nbImages' and the size of images.
 * Save result in matrix : intrinsic_matrix / distortion_coeffs / rotation_vector / translation_vector
 * if "save" is true, it saves intrinsic_matrix and distortion_coeffs in ".xml" files.
 *\n
 * @param nbImages, width, height
 * @return the retroprojection error compute by OpenCV during the calibration
*/
float calibrage::computeOpenCV(int nbImages, int width, int height)
{
   int nbPointInImage = currentTestPattern.nbPoints;
   float retroprojection_error;

   CvMat *object_points = cvCreateMat(nbPointInImage*nbImages ,3 ,CV_32FC1);
   CvMat *image_points  = cvCreateMat(nbPointInImage*nbImages ,2 ,CV_32FC1);
   CvMat *point_counts  = cvCreateMat(  nbImages, 1, CV_32SC1);
   intrinsic_matrix = cvCreateMat(3,3,CV_32FC1);
   distortion_coeffs = cvCreateMat(1,5,CV_32FC1);
   rotation_vector = cvCreateMat(nbImages,3,CV_32FC1);
   translation_vector = cvCreateMat(nbImages,3,CV_32FC1);

   for(int k=0;k<nbImages;k++)
   {
      for(int i=0;i<nbPointInImage;i++)
      {
         CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,0) = currentTestPattern.grid.at(i).get_oX(); 
         CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,1) = currentTestPattern.grid.at(i).get_oY();
         CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,2) = currentTestPattern.grid.at(i).get_oZ();
         CV_MAT_ELEM( *image_points, float,k*nbPointInImage + i,0) = listImage[k].at(i).get_u();
         CV_MAT_ELEM( *image_points, float,k*nbPointInImage + i,1) = listImage[k].at(i).get_v();
      }
   }
   cvZero(distortion_coeffs);
   cvZero(point_counts);
   cvSet(point_counts,cvScalar(nbPointInImage));

   cvSetIdentity(intrinsic_matrix);
   CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = Focal;
   CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = Focal;
   CV_MAT_ELEM( *intrinsic_matrix, float, 0, 2 ) = width/2;
   CV_MAT_ELEM( *intrinsic_matrix, float, 1, 2 ) = height/2;

   CvSize image_size = cvSize( width,height); 
      
   /* launch calibration */
   retroprojection_error = cvCalibrateCamera2(object_points,image_points,point_counts,image_size,
                                              intrinsic_matrix,distortion_coeffs,
                                              rotation_vector,translation_vector,
                                              CV_CALIB_USE_INTRINSIC_GUESS/* + CV_CALIB_RATIONAL_MODEL  better with fish-eye lens */,
                                              cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, DBL_EPSILON));

//   printf("\nOpenCV Retrojection Error: %lf\n",retroprojection_error);

//   printf( "Intrinsic matrix for opencv calibration :\n");
//   for( size_t i = 0; i < 3; i++ ) 
//   {
//      for( size_t j = 0; j < 3; j++ ) 
//         // Observe the type used in the template
//         printf( " %.3f ", at(intrinsic_matrix,i,j));
//      printf( "\n");
//   }
//   printf( "distortion coeffs for opencv calibration :\n");
//   for( size_t j = 0; j < 5; j++ )
//      // Observe the type used in the template
//      printf( " %.3f ", at(distortion_coeffs,0,j));
//   printf("\n\n");

   /* Save the intrinsics and distortions */
   if(m_save == true)
   {
      filename = repertoire_intrinsic + m_camera + "_calib.xml";
      FileStorage fs(filename, CV_STORAGE_WRITE);
      if( fs.isOpened() )
      {
         fs << "width" << image_size.width << "height" << image_size.height
            << "M" << intrinsic_matrix << "D" <<  distortion_coeffs;
         fs.release();
      }
      else
         cout << "Error: can not save the intrinsic parameters\n";
   }

   return retroprojection_error;
}

/**
* calibrate
 * @fn void calibrage::calibrate(vpImage<unsigned char> &image, int methode, int nbImages)
 * @brief compute the calibration algorithms
 * @details This method computes calibration algorithms using a particular method : ViSP, ViSP with distortion or OpenCV
 *\n
 * @param image, methode, nbImages
*/
void calibrage::calibrate(vpImage<unsigned char> &image, int methode, int nbImages)
{
   cout << "Running calibration ... ";
   fflush(stdout);
   switch(methode)
   {
      case VISP:
         computeCalibrationViSP(vpCalibration::CALIB_VIRTUAL_VS);
         break;
      case VISP_DIST:
         computeCalibrationViSP(vpCalibration::CALIB_VIRTUAL_VS_DIST);
         break;
      case OPENCV:
         computeOpenCV(nbImages,image.getWidth(),image.getHeight());
         break;
   }
   cout << "done\n" << endl;
}

/**
* validatePose
 * @fn bool calibrage::validatePose(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsTotal)
 * @brief Ask a pose validation
 * @details Let the user select if a pose will be use to compute the calibration.
 * pt is the image points list found. nbPointsTotal is the number of points to find in the image
 * Save result in table_cal and listImage
 * if save = TRUE, table_cal save in imagename.txt
 *\n
 * @param image, pt, nbPointsTotal
 * @return TRUE, if the current pose is candidated for calibration
*/
bool calibrage::validatePose(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsTotal)
{  
   if(m_click)
   {
      vpImagePoint ip;
      vpMouseButton::vpMouseButtonType button;
      vpDisplay::getClick(image, ip, button) ; 
      switch(button)
      {
         case 1 : //left
            cout << "   Left click -> pose validated" << endl;
            break;
         case 2 : //middle
            cout << "   Middle click -> pose ignored" << endl;   
            niter++;
            return false;
         case 3 : //right
            cout << "   Right click -> retry" << endl;
            switch(currentTestPattern.type)
            {
               case DOT2D :
               {
                  if(!findDots(image, pt,currentTestPattern.nbPoints,filename))
                  { 
                     iter--;
                     return false;
                  }
                  break;
               }
               case GRID2D:
               {
                  if(!findCross(image, pt,currentTestPattern.nbPoints,filename))
                  { 
                     iter--;
                     return false;
                  }
                  break;
               }
               case DOT3D :
               {
                  if(!findDots(image, pt,currentTestPattern.nbPoints,filename))
                  { 
                     iter--;
                     return false;
                  }
                  break;
               }
            }
            break;
      }
   }
   else
      cout<<endl;   
   
   listImage[nbImgCal].clear();

   /* Add points to the list */
   for(int i=0; i<nbPointsTotal; i++)
   {  
      table_cal[niter].addPoint(currentTestPattern.grid[i].get_oX(),currentTestPattern.grid[i].get_oY(),currentTestPattern.grid[i].get_oZ(),pt[i]);
      listImage[nbImgCal].push_back(pt[i]);
   }

   if(m_save == true)
   {
         std::string::size_type found = m_imageFilenames_1.at(0).find_last_of("/\\");
         std::string::size_type found2 = m_imageFilenames_1.at(0).find_last_of(".");
         filename = repertoire_calibtab + m_imageFilenames_1.at(niter).substr(found+1,found2-found-1) + ".txt";
         table_cal[niter].writeData(filename.c_str());      
   }
   validImage[niter]=1;
   nbImgCal = nbImgCal + validImage[niter];
   niter++ ;  
   return true;
}

/**
* poseEstimation
 * @fn int calibrage::poseEstimation(int methode, int nbImages)
 * @brief compute the extrinsic parameters
 * @details Save result in homogeneousMatrixTable[] for ViSP and 
 * translation_vector & rotation_vector for OpenCV
 *\n
 * @param methode, nbImages
 * @return 0 if one image not contain all the requiered point
*/
int calibrage::poseEstimation(int methode, int nbImages)
{
   if(methode == VISP || methode == VISP_DIST)
   {
      homogeneousMatrixTable = new vpHomogeneousMatrix[nbImages];

      for(int k=0; k<nbImages; k++)
      {
         vpPose pose; pose.clearPoint();
         vpHomogeneousMatrix mH; mH.init();
         double x=0, y=0;
         int l = currentTestPattern.nbX, c = currentTestPattern.nbY, n = currentTestPattern.nbPoints;
         vpRotationMatrix R;
         vpTranslationVector T;

         if(currentTestPattern.type==DOT2D || currentTestPattern.type==GRID2D)
         {
            vpPoint pt;
            pt = currentTestPattern.grid.at( 0 ); vpPixelMeterConversion::convertPoint(cam, listImage[k].at( 0 ), x, y); pt.set_x(x); pt.set_y(y); pose.addPoint(pt);
            pt = currentTestPattern.grid.at(c-1); vpPixelMeterConversion::convertPoint(cam, listImage[k].at(c-1), x, y); pt.set_x(x); pt.set_y(y); pose.addPoint(pt);
            pt = currentTestPattern.grid.at(n-l); vpPixelMeterConversion::convertPoint(cam, listImage[k].at(n-l), x, y); pt.set_x(x); pt.set_y(y); pose.addPoint(pt);
            pt = currentTestPattern.grid.at(n-1); vpPixelMeterConversion::convertPoint(cam, listImage[k].at(n-1), x, y); pt.set_x(x); pt.set_y(y); pose.addPoint(pt);
         }
         else if(currentTestPattern.type==DOT3D)
         {
            for(int i=0;i<6;i++)
            {
               vpPoint pt = currentTestPattern.grid.at(i*2);
               vpPixelMeterConversion::convertPoint(cam, listImage[k].at(2*i), x, y);
               pt.set_x(x); pt.set_y(y); pose.addPoint(pt);
            }
         }
        
         int currentIndex;
         switch(currentTestPattern.type)
         {
            case DOT2D:
            case GRID2D:
            {
               currentIndex = 2; 
               break;
            }
            case DOT3D :
            {
               currentIndex = 3; 
               break;
            }
         }
         // choose Lagrange for 2d pattern (select(2)), Dementhon for 3d (select (3))
         switch(currentIndex)
         {
            case 0: pose.computePose(vpPose::LAGRANGE,mH); break;
            case 1: pose.computePose(vpPose::DEMENTHON,mH); break;
            case 2: pose.computePose(vpPose::LAGRANGE_LOWE,mH); break;
            case 3: pose.computePose(vpPose::DEMENTHON_LOWE,mH); break;
            case 4: pose.computePose(vpPose::LAGRANGE_VIRTUAL_VS,mH); break;
            case 5: pose.computePose(vpPose::DEMENTHON_VIRTUAL_VS,mH); break;
         }
         homogeneousMatrixTable[k] = mH;
         homogeneousMatrixTable[k].extract(R);
         homogeneousMatrixTable[k].extract(T);
      }
      /*printf("rotation vector visp\n"); 
      for(int k=0; k<nbImages; k++)
      {
         vpRotationMatrix R;
         homogeneousMatrixTable[k].extract(R);
         R.printVector();
      }  */
   }
   if(methode == OPENCV)
   {
      cvReleaseMat(&rotation_vector);
      cvReleaseMat(&translation_vector);
      rotation_vector = cvCreateMat(nbImages,3,CV_32FC1);
      translation_vector = cvCreateMat(nbImages,3,CV_32FC1);

      int nbPointInImage = currentTestPattern.nbPoints;

      CvMat *rot = cvCreateMat(1,3,CV_32FC1);
      CvMat *trans = cvCreateMat(1,3,CV_32FC1);
      CvMat *object_points = cvCreateMat(nbPointInImage ,3 ,CV_32FC1);
      CvMat *image_points  = cvCreateMat(nbPointInImage ,2 ,CV_32FC1);

      for(int k=0;k<nbImages;k++)
      {
         for(int i=0;i<nbPointInImage;i++)
         {
            CV_MAT_ELEM( *object_points,float,i,0) = currentTestPattern.grid.at(i).get_oX();
            CV_MAT_ELEM( *object_points,float,i,1) = currentTestPattern.grid.at(i).get_oY();
            CV_MAT_ELEM( *object_points,float,i,2) = currentTestPattern.grid.at(i).get_oZ();
            CV_MAT_ELEM( *image_points, float,i,0) = listImage[k].at(i).get_u();
            CV_MAT_ELEM( *image_points, float,i,1) = listImage[k].at(i).get_v();
         }
         cvFindExtrinsicCameraParams2(object_points,image_points,intrinsic_matrix,distortion_coeffs,rot,trans);

         for(int i=0;i<3;i++)
         {
            CV_MAT_ELEM( *rotation_vector,float,k,i) = CV_MAT_ELEM( *rot,float,0,i);
            CV_MAT_ELEM( *translation_vector,float,k,i) = CV_MAT_ELEM( *trans,float,0,i);
         }
      }
   }
   return 1;
}

/**
* retroprojection
 * @fn vector<vpImagePoint> calibrage::retroprojection(vector<vpPoint>pt3D, int nbImages, string method, bool withDistortion)
 * @brief computes the retroprojection
 * @details Need : list of 3D points coordinates of the testpattern, the images number for images
 * 2 methods are available : "opencv" and "visp"
 * 2 options are available : withDistortion = true (default), withDistortion = false
 *\n
 * @param pt3D, nbImages, method, withDistortion
 * @return a list of 2D vpImagePoint
*/
vector<vpImagePoint> calibrage::retroprojection(vector<vpPoint>pt3D, int nbImages, string method, bool withDistortion)
{
   vector<vpImagePoint> ptProjImage;
   if(method == "opencv")
   {
      CvMat *object_points = cvCreateMat(currentTestPattern.nbPoints ,3 ,CV_32FC1);
      CvMat *image_points = cvCreateMat(currentTestPattern.nbPoints ,2 ,CV_32FC1);
      CvMat *rotation = cvCreateMat(1,3,CV_32FC1);
      CvMat *translation = cvCreateMat(1,3,CV_32FC1);

      for(int k=0;k<nbImages;k++)
      {
         for(unsigned int i=0;i<pt3D.size();i++)
         {
            CV_MAT_ELEM( *object_points,float,i,0) = pt3D.at(i).get_X();
            CV_MAT_ELEM( *object_points,float,i,1) = pt3D.at(i).get_Y();
            CV_MAT_ELEM( *object_points,float,i,2) = pt3D.at(i).get_Z();
         }
         cvGetRow(rotation_vector,rotation,k);
         cvGetRow(translation_vector,translation,k);
         cvProjectPoints2(object_points,rotation,translation,intrinsic_matrix,distortion_coeffs,image_points);

         for(int i=0;i<image_points->rows;i++)
         {
            vpImagePoint pt(CV_MAT_ELEM( *image_points,float,i,1),CV_MAT_ELEM( *image_points,float,i,0));
            ptProjImage.push_back( pt );
         }
      }
   }
   if(method == "visp")
   {
      for(int k=0;k<nbImages;k++)
      {
         for(unsigned int i=0; i<pt3D.size();i++)
         {
            vpPoint pt = pt3D.at(i);
            pt.project(homogeneousMatrixTable[k]);
            vpImagePoint imagePt;
            if(withDistortion)
               vpMeterPixelConversion::convertPointWithDistortion(cam,pt.p[0],pt.p[1],imagePt);
            else
               vpMeterPixelConversion::convertPointWithoutDistortion(cam,pt.p[0],pt.p[1],imagePt);

            ptProjImage.push_back(imagePt);
         }
      }
   }
   return ptProjImage;
}

/**
* showRetroprojection
 * @fn void calibrage::showRetroprojection(vpImage<unsigned char> &image, int methode, int nbImages)
 * @brief compute and draw the retroprojection in external window
 *\n
 * @param image, methode, nbImages
*/
void calibrage::showRetroprojection(vpImage<unsigned char> &image, int methode, int nbImages)
{
   char comment[FILENAME_MAX];
   vpDisplayOpenCV displayRetro;
   filename = m_imageFilenames_1.at(0);
   vpImageIo::read(image, filename);
   displayRetro.init(image,100,200,"Retroprojection");

   if(!poseEstimation(methode, nbImages)) {cout << "Error during Estimation" << endl; return; }

   vector<vpImagePoint> retroprojPointsViSP, retroprojPointsViSPwithoutDist, retroprojPointsOpenCV;
   vector<vpImagePoint> imagePoints; imagePoints.clear();
   for(int k=0; k<nbImages;k++)
      for(unsigned int i=0; i<listImage[k].size();i++)
         imagePoints.push_back(listImage[k].at(i));

   if(methode == VISP)
   {
      retroprojPointsViSPwithoutDist = retroprojection(currentTestPattern.grid,nbImages,"visp",false); //without distortion
      float retroprojErrorViSPwithoutDist = computeRetroprojectionError(retroprojPointsViSPwithoutDist,imagePoints);
      cout << "Visp Retrojection Error without distortion : " << retroprojErrorViSPwithoutDist << " pixels / image\n"<< endl;
   }
   if(methode == VISP_DIST)
   {
      retroprojPointsViSP = retroprojection(currentTestPattern.grid,nbImages,"visp");
      float retroprojErrorViSPwithDist = computeRetroprojectionError(retroprojPointsViSP,imagePoints);
      cout << "Visp Retrojection Error:   " << retroprojErrorViSPwithDist << " pixels / image\n" << endl;
   }
   if(methode == OPENCV)
   {
      retroprojPointsOpenCV = retroprojection(currentTestPattern.grid,nbImages,"opencv");
      float retroprojErrorOpenCV = computeRetroprojectionError(retroprojPointsOpenCV,imagePoints);
      cout << "OpenCV Retrojection Error: " << retroprojErrorOpenCV << " pixels" << endl;// / image\n" << endl;
   }

   //DISPLAY ERROR
   int check = 0;
   for(int k=0;k<m_nimages;k++)
   {
      if(validImage[k]==1)
      {
         int n = currentTestPattern.nbPoints;
         filename = m_imageFilenames_1.at(k);
         vpImageIo::read(image,filename);
         vpDisplay::display(image);

         for(int i=0;i<currentTestPattern.nbPoints;i++)
         {
            vpDisplay::displayCross(image,imagePoints.at(i+check*n),10,vpColor::green,2);
            if(methode == VISP)     vpDisplay::displayCross(image,retroprojPointsViSPwithoutDist.at(i+check*n),10,vpColor::blue,1);
            if(methode == VISP_DIST)     vpDisplay::displayCross(image,retroprojPointsViSP.at(i+check*n),10,           vpColor::blue,  1);
            if(methode == OPENCV)     vpDisplay::displayCross(image,retroprojPointsOpenCV.at(i+check*n),10,         vpColor::blue,1);
         }
         vpDisplay::displayCharString(image,10,10,"Base points",vpColor::green);
         vpDisplay::displayCharString(image, image.getHeight() -15, 10,filename.c_str(),vpColor::orange);
         if(methode == VISP)
         {
            sprintf(comment,"Visp projection without distortion %lf pixels",computeRetroprojectionError(retroprojPointsViSPwithoutDist,imagePoints,check*n,(check+1)*n));
            vpDisplay::displayCharString(image,20,10,&comment[0],vpColor::blue);
         }
         if(methode == VISP_DIST)
         {
            sprintf(comment,"Visp projection %lf pixel",computeRetroprojectionError(retroprojPointsViSP,imagePoints,check*n,(check+1)*n));
            vpDisplay::displayCharString(image,30,10,&comment[0],vpColor::blue);
         }
         if(methode == OPENCV)
         {
            sprintf(comment,"OpenCV projection %lf pixels",computeRetroprojectionError(retroprojPointsOpenCV,imagePoints,check*n,(check+1)*n));
            vpDisplay::displayCharString(image,40,10,&comment[0],vpColor::blue);
         }
         check++;
         vpDisplay::flush(image);
         if(m_click)
            vpDisplay::getClick(image);
      }
   }
   vpDisplay::close(image);
}

/**
* modeMono
 * @fn int calibrage::modeMono()
 * @brief Calibration processus for a single camera
 *\n
 * @return 0
*/
int calibrage::modeMono()
{                                  
   if(!defPattern("./../data/mire.cfg"))
      return 0;

   if(!loadImage(imageViSP))
      return 0;

   table_cal = new vpCalibration[m_nimages]; //coordinates tab : [X, Y, Z, u, v]
   listImage = new vector<vpImagePoint>[m_nimages];

   vpDisplayOpenCV display;

   // set the new image name
   filename = m_imageFilenames_1.at(iter);
   vpImageIo::read(imageViSP, filename);
   display.init(imageViSP,100,200,"Calibration");

   //Initialisation of camera parameters
   //Initial camera parameters have to be close of real camera parameters
   cam.initPersProjWithDistortion(Focal,Focal,imageViSP.getWidth()/2,imageViSP.getHeight()/2,0,0);

   while (iter < m_nimages) 
   {
      try
      {
         filename = m_imageFilenames_1.at(iter);
         std::string::size_type found = m_imageFilenames_1.at(0).find_last_of("/\\");
         std::string::size_type found2 = m_imageFilenames_1.at(0).find_last_of(".");
         string checkFile = repertoire_calibtab + m_imageFilenames_1.at(iter).substr(found+1,found2-found-1) + ".txt";
         cout << "read : " << filename;
         fflush(stdout);
         vpImageIo::read(imageViSP, filename);
         vpDisplay::display(imageViSP);

         int nbPointsTotal = currentTestPattern.nbPoints;
         vpImagePoint p[nbPointsTotal];

         if(!loadCalibTab(checkFile,p))
            if(!findImagePoints(imageViSP, p,filename))
               continue;

         displayPoints(imageViSP, p,nbPointsTotal,filename);
         validatePose(imageViSP, p, nbPointsTotal);
      }
      catch(...){return(-1);}
      iter++;
   }  
   vpDisplay::close(imageViSP); 

   if(nbImgCal==0)
   {
      cout << "\nNo image -> No Calibration\n" << endl;      
      return 0;
   }
   else if(nbImgCal==1)
   {
      cout << "\nOnly one image -> No Calibration\n" << endl;      
      return 0;
   }
   else
      cout << "\n" << nbImgCal <<" images sur " << m_nimages << " utilisées pour la calibration\n" << endl;   
    
   calibrate(imageViSP, OPENCV, nbImgCal);
//   calibrate(imageViSP, VISP_DIST, nbImgCal);

   printf( "Intrinsic matrix for opencv calibration :\n");
   for( size_t i = 0; i < 3; i++ ) 
   {
      for( size_t j = 0; j < 3; j++ ) 
         // Observe the type used in the template
         printf( " %.6f ", at(intrinsic_matrix,i,j));
      printf( "\n");
   }
   printf( "distortion coeffs for opencv calibration :\n");
   for( size_t j = 0; j < 5; j++ )
      // Observe the type used in the template
      printf( " %.6f ", at(distortion_coeffs,0,j));
   printf("\n\n");

   showRetroprojection(imageViSP, OPENCV,nbImgCal);
//   showRetroprojection(imageViSP, VISP_DIST,nbImgCal);

   printf("\n");

   return 0;
}
