/** 
 * \file calibrageStereo.cpp
 *
 * \brief <b>Implementation file for method to Calibrate stereo camera</b>. 
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
* loadImageStereo
 * @fn bool calibrage::loadImageStereo(vpImage<unsigned char> image_left, vpImage<unsigned char> image_right)
 * @brief load 2 PGM image files
 * @details This method load the image files name "opt_ppath_left", "opt_ppath_right" and number "iter". 
 * "opt_ppath_left" and "opt_ppath_right" are set in init() method. "iter" is set in init() method
 * If "opt_video is true, this method calls recordImageSequenceStereo() method and set "opt_nimages" instead.
 *\n
 * @param gray image_left, image_right
 * @return TRUE, if the first images are loaded
*/
bool calibrage::loadImageStereo(vpImage<unsigned char> image_left, vpImage<unsigned char> image_right)
{
   filename_left = m_imageFilenames_1.at(iter);
   filename_right = m_imageFilenames_2.at(iter);
   // Read the PGM image named "filename" on the disk, and put the
   // bitmap into the image structure I.  I is initialized to the
   // correct size
   // exception readPGM may throw various exception if, for example,
   // the file does not exist, or if the memory cannot be allocated
   try
   {
      vpImageIo::read(image_left, filename_left) ;
      vpImageIo::read(image_right, filename_right) ;
   }
   catch(...)
   {
      // an exception is throwned if an exception from readPGM has been catched
      // here this will result in the end of the program
      // Note that another error message has been printed from readPGM
      // to give more information about the error
      cerr << endl
      << "ERROR:" << endl;
      cerr << "  Cannot read " << filename_left << " or " << filename_right << endl;
      return(-1);
   }
   return true;
}

/**
 * computeCalibrationViSPStereo
 * @fn int calibrage::computeCalibrationViSPStereo(vpCalibration::vpCalibrationMethodType methode)
 * @brief computes the ViSP calibration using a specific method
 * @details This method performs a calibration using ViSP for each camera. 
 * 2 methodes available : calibration without distortion and calibration with it.
 * "save" is set in init() method. 
 * If "save" is true, calibration data are save in ".txt" files for each image and intrinsic camera parameters are write in a ".xml" file
 *\n
 * @param methode
 * @return 0 if the computation was managed succeed.
*/
int calibrage::computeCalibrationViSPStereo(vpCalibration::vpCalibrationMethodType methode)
{ 
   int result_left =  vpCalibration::computeCalibrationMulti(methode,m_nimages,table_cal_left,cam_left,false);
   int result_right = vpCalibration::computeCalibrationMulti(methode,m_nimages,table_cal_right,cam_right,false);

   if(methode == vpCalibration::CALIB_VIRTUAL_VS)
   {
      if((result_left || result_right) != 0)
         cout << "Calibration without distortion failed." << endl;
   }
   else if (methode == vpCalibration::CALIB_VIRTUAL_VS_DIST)
   {
      if((result_left || result_right) != 0)
         cout << "Calibration with distortion failed." << endl;
   }
//   cam_left.printParameters();
//   cam_right.printParameters();

   if(m_save == true)
   {
      // write camera Parameters in a xml file
      vpXmlParserCamera xml;
      if(methode == vpCalibration::CALIB_VIRTUAL_VS)
      {
         if(result_left == 0)
         { 
            filename_left = repertoire_intrinsic + "visp_calibrage_stereo_left.xml";
            remove(filename_left.c_str());
            int resultSaving = xml.save(cam_left, filename_left.c_str(), "Camera_left", I_left.getWidth(), I_left.getHeight());
            if(resultSaving != vpXmlParserCamera::SEQUENCE_OK)
               cout << "Failed to save the camera parameters without distortion in visp_calibrage_stereo_left.xml" << endl;
         }
         if(result_right == 0)
         { 
            filename_right = repertoire_intrinsic + "visp_calibrage_stereo_right.xml";
            remove(filename_right.c_str());
            int resultSaving = xml.save(cam_right, filename_right.c_str(), "Camera_right", I_right.getWidth(), I_right.getHeight());
            if(resultSaving != vpXmlParserCamera::SEQUENCE_OK)
               cout << "Failed to save the camera parameters without distortion in visp_calibrage_stereo_right.xml" << endl;
         }
      }
      if(methode == vpCalibration::CALIB_VIRTUAL_VS_DIST)
      {
         if(result_left == 0) 
         {
            filename_left = repertoire_intrinsic + "visp_calibrage_dist_stereo_left.xml";
            remove(filename_left.c_str());
            int resultSavingDist =  xml.save(cam_left, filename_left.c_str(), "Camera_left", I_left.getWidth(), I_left.getHeight());
            if(resultSavingDist != vpXmlParserCamera::SEQUENCE_OK )
               cout << "Failed to save the camera parameters with distortion in visp_calibrage_dist_stereo_left.xml" << endl;
         }
         if(result_right == 0) 
         {
            filename_right = repertoire_intrinsic + "visp_calibrage_dist_stereo_right.xml";
            remove(filename_right.c_str());
            int resultSavingDist =  xml.save(cam_right, filename_right.c_str(), "Camera_right", I_right.getWidth(), I_right.getHeight());
            if(resultSavingDist != vpXmlParserCamera::SEQUENCE_OK )
               cout << "Failed to save the camera parameters with distortion in visp_calibrage_dist_stereo_right.xml" << endl;
         }
      }
      vpXmlParser::cleanup();
   }
   return 0;
}

/**
 * computeOpenCVStereo
 * @fn float calibrage::computeOpenCVStereo(int nbImages, int width, int height)
 * @brief computes the calibration using OpenCV 
 * @details This function needs the number of images used 'nbImages' and the size of images.
 * Save result in matrix : intrinsic_matrix / distortion_coeffs / rotation_vector / translation_vector
 * Print intrinsic_matrix and distortion_coeff on the terminal.
 * if "save" is true, it saves intrinsic_matrix and distortion_coeffs in ".xml" files.
 *\n
 * @param nbImages, width, height
 * @return 0
*/
float calibrage::computeOpenCVStereo(int nbImages, int width, int height)
{
   int nbPointInImage = currentTestPattern.nbPoints;

   CvMat *object_points = cvCreateMat(nbPointInImage*nbImages ,3 ,CV_32FC1);
   CvMat *image_points_left  = cvCreateMat(nbPointInImage*nbImages ,2 ,CV_32FC1);
   CvMat *image_points_right  = cvCreateMat(nbPointInImage*nbImages ,2 ,CV_32FC1);
   CvMat *point_counts  = cvCreateMat(  nbImages, 1, CV_32SC1);

   intrinsic_matrix_left = cvCreateMat(3,3,CV_32FC1);
   intrinsic_matrix_right = cvCreateMat(3,3,CV_32FC1);
   distortion_coeffs_left = cvCreateMat(1,5,CV_32FC1);
   distortion_coeffs_right = cvCreateMat(1,5,CV_32FC1);
   rotation_vector_left = cvCreateMat(nbImages,3,CV_32FC1);
   rotation_vector_right = cvCreateMat(nbImages,3,CV_32FC1);
   translation_vector_left = cvCreateMat(nbImages,3,CV_32FC1);
   translation_vector_right = cvCreateMat(nbImages,3,CV_32FC1);

   for(int k=0;k<nbImages;k++)
   {
      for(int i=0;i<nbPointInImage;i++)
      {
         CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,0) = currentTestPattern.grid.at(i).get_oX(); 
         CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,1) = currentTestPattern.grid.at(i).get_oY();
         CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,2) = currentTestPattern.grid.at(i).get_oZ();
         CV_MAT_ELEM( *image_points_left, float,k*nbPointInImage + i,0) = listImage_left[k].at(i).get_u();
         CV_MAT_ELEM( *image_points_left, float,k*nbPointInImage + i,1) = listImage_left[k].at(i).get_v();
         CV_MAT_ELEM( *image_points_right, float,k*nbPointInImage + i,0) = listImage_right[k].at(i).get_u();
         CV_MAT_ELEM( *image_points_right, float,k*nbPointInImage + i,1) = listImage_right[k].at(i).get_v();
      }
   }
   cvZero(distortion_coeffs_left);
   cvZero(distortion_coeffs_right);
   cvZero(point_counts);
   cvSet(point_counts,cvScalar(nbPointInImage));

   cvSetIdentity(intrinsic_matrix_left); 
   CV_MAT_ELEM( *intrinsic_matrix_left, float, 0, 0 ) = Focal;
   CV_MAT_ELEM( *intrinsic_matrix_left, float, 1, 1 ) = Focal;
   CV_MAT_ELEM( *intrinsic_matrix_left, float, 0, 2 ) = width/2;
   CV_MAT_ELEM( *intrinsic_matrix_left, float, 1, 2 ) = height/2;
   cvSetIdentity(intrinsic_matrix_right);
   CV_MAT_ELEM( *intrinsic_matrix_right, float, 0, 0 ) = Focal;
   CV_MAT_ELEM( *intrinsic_matrix_right, float, 1, 1 ) = Focal;
   CV_MAT_ELEM( *intrinsic_matrix_right, float, 0, 2 ) = width/2;
   CV_MAT_ELEM( *intrinsic_matrix_right, float, 1, 2 ) = height/2;

   CvSize image_size = cvSize( width,height); 

   //launch calibration
   float repro_error_left = cvCalibrateCamera2(object_points,image_points_left,point_counts,image_size,
                                               intrinsic_matrix_left,distortion_coeffs_left,
                                               rotation_vector_left,translation_vector_left,
                                               CV_CALIB_USE_INTRINSIC_GUESS, cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, DBL_EPSILON));
   float repro_error_right = cvCalibrateCamera2(object_points,image_points_right,point_counts,image_size,
                                                intrinsic_matrix_right,distortion_coeffs_right,
                                                rotation_vector_right,translation_vector_right,
                                                CV_CALIB_USE_INTRINSIC_GUESS, cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, DBL_EPSILON));
//   printf("\nrepro_error_left: %lf, repro_error_right: %lf\n",repro_error_left,repro_error_right);

   if(m_save == true)
   {
      filename = repertoire_intrinsic + m_camera_left + "_calib.xml";
      FileStorage fs(filename, CV_STORAGE_WRITE);
      if( fs.isOpened() )
      {
         fs << "width" << image_size.width << "height" << image_size.height
            << "M" << intrinsic_matrix_left << "D" << distortion_coeffs_left;
         fs.release();
      }
      else
         cout << "Error: can not save the intrinsic parameters for "<< m_camera_left << "\n";

      filename = repertoire_intrinsic + m_camera_right + "_calib.xml";
      fs.open(filename, CV_STORAGE_WRITE);
      if( fs.isOpened() )
      {
         fs << "width" << image_size.width << "height" << image_size.height
            << "M" << intrinsic_matrix_right << "D" << distortion_coeffs_right;
         fs.release();
      }
      else
         cout << "Error: can not save the intrinsic parameters for "<< m_camera_right << "\n";
   }
   return 0;
}

/**
* calibrateStereo
 * @fn void calibrage::calibrateStereo(vpImage<unsigned char> &image, int methode, int nbImages)
 * @brief compute the calibration algorithms
 * @details This method computes calibration algorithms using ViSP or OpenCV
 *\n
 * @param image, methode, nbImages
*/
void calibrage::calibrateStereo(vpImage<unsigned char> &image, int methode, int nbImages)
{
   cout << "Running stereo calibration ... ";
   fflush(stdout);
   switch(methode)
   {
      case VISP:
         computeCalibrationViSPStereo(vpCalibration::CALIB_VIRTUAL_VS);
         break;
      case VISP_DIST:
         computeCalibrationViSPStereo(vpCalibration::CALIB_VIRTUAL_VS_DIST);
         break;
      case OPENCV:
         computeOpenCVStereo(nbImages,image.getWidth(),image.getHeight());
         break;
   }
   cout << "done\n" << endl;
}

/**
* validatePoseStereo
 * @fn bool calibrage::validatePoseStereo(vpImage<unsigned char> &image_left, vpImage<unsigned char> &image_right, vpImagePoint pt_left[], vpImagePoint pt_right[], int nbPointsTotal)
 * @brief Ask a pose validation
 * @details Let the user select if a pose will be use to compute the calibration.
 * pt_left and pt_right are the image points list found. nbPointsTotal is the number of points to find in the image
 * Save result in table_cal_* and listImage_*
 * if save = TRUE, table_cal_* save in imagename_*.txt
 *\n
 * @param image_left, image_right, pt_left, pt_right, nbPointsTotal
 * @return TRUE, if the current pose is candidated for calibration
*/
bool calibrage::validatePoseStereo(vpImage<unsigned char> &image_left, vpImage<unsigned char> &image_right, vpImagePoint pt_left[], vpImagePoint pt_right[], int nbPointsTotal)
{  
   if(m_click)
   {
      bool isover =false;
      while(!isover)
      {
         vpDisplay::flush(image_left);
         vpDisplay::flush(image_right);
         vpImagePoint ip;
         vpMouseButton::vpMouseButtonType button;
         if(vpDisplay::getClick(image_left, ip, button, false)||vpDisplay::getClick(image_right, ip, button, false))
            switch(button)
            {
               case 1:
                  cout << "   Left click -> pose validated." << endl;
                  cout<<endl;
                  isover = true;
                  break;
               case 2:
                  cout << "   Middle click -> pose ignored." << endl;   
                  cout<<endl;
                  niter++;
                  return false;
               case 3:
                  cout << "   Right click -> retry." << endl;
                  switch(currentTestPattern.type)
                  {
                     case DOT2D :
                     {
                        if(!findDots(image_left, pt_left,currentTestPattern.nbPoints,filename_left))
                        { 
                           iter--;
                           return false;
                        }
                        if(!findDots(image_right, pt_right,currentTestPattern.nbPoints,filename_right))
                        { 
                           iter--;
                           return false;
                        }
                        break;
                     }
                     case GRID2D:
                     {
                        if(!findCross(image_left, pt_left,currentTestPattern.nbPoints,filename_left))
                        { 
                           iter--;
                           return false;
                        }
                        if(!findCross(image_right, pt_right,currentTestPattern.nbPoints,filename_right))
                        { 
                           iter--;
                           return false;
                        }
                        break;
                     }
                     case DOT3D :
                     {
                        if(!findDots(image_left, pt_left,currentTestPattern.nbPoints,filename_left))
                        { 
                           iter--;
                           return false;
                        }
                        if(!findDots(image_right, pt_right,currentTestPattern.nbPoints,filename_right))
                        { 
                           iter--;
                           return false;
                        }
                        break;
                     }
                  }
                  isover = true;
                  break;
            }
      }
   }
   else
      cout<<endl;
 
   listImage_left[nbImgCal].clear();   
   listImage_right[nbImgCal].clear(); 
   //Add points to the list and save points
   for(int i=0; i<nbPointsTotal; i++)
   {   
      table_cal_left[niter].addPoint(currentTestPattern.grid[i].get_oX(),currentTestPattern.grid[i].get_oY(),currentTestPattern.grid[i].get_oZ(),pt_left[i]);
      table_cal_right[niter].addPoint(currentTestPattern.grid[i].get_oX(),currentTestPattern.grid[i].get_oY(),currentTestPattern.grid[i].get_oZ(),pt_right[i]);
      listImage_left[nbImgCal].push_back(pt_left[i]);
      listImage_right[nbImgCal].push_back(pt_right[i]);
   }

   if(m_save == true)
   {
         std::string::size_type found = m_imageFilenames_1.at(0).find_last_of("/\\");
         std::string::size_type found2 = m_imageFilenames_1.at(0).find_last_of(".");
         filename_left =   repertoire_calibtab + m_imageFilenames_1.at(niter).substr(found+1,found2-found-1) + ".txt";

         found = m_imageFilenames_2.at(0).find_last_of("/\\");
         found2 = m_imageFilenames_2.at(0).find_last_of(".");
         filename_right =   repertoire_calibtab + m_imageFilenames_2.at(niter).substr(found+1,found2-found-1) + ".txt";

         table_cal_left[niter].writeData(filename_left.c_str());
         table_cal_right[niter].writeData(filename_right.c_str());
   }
   validImage[niter]=1;
   nbImgCal = nbImgCal + validImage[niter];
   niter++ ; 
   return true; 
}

/**
* poseEstimationStereo
 * @fn int calibrage::poseEstimationStereo(int methode, int nbImages, int width, int height)
 * @brief compute the extrinsic parameters
 * @details Save result in homogeneousMatrixTable[] for ViSP and 
 * translation_vector & rotation_matrix for OpenCV between the two cameras
 *\n
 * @param methode, nbImages, width, height
 * @return 0 if one image not contain all the requiered point
*/
int calibrage::poseEstimationStereo(int methode, int nbImages, int width, int height)
{
   if(methode == VISP || methode == VISP_DIST)
   {
      homogeneousMatrixTable_left = new vpHomogeneousMatrix[nbImages];
      homogeneousMatrixTable_right = new vpHomogeneousMatrix[nbImages];

      for(int k=0; k<nbImages; k++)
      {
            // we can use homogeneousMatrixTable[k] = table_cal[k].cMo_dist;
            vpPose pose_left; pose_left.clearPoint();
            vpPose pose_right; pose_right.clearPoint();
            vpHomogeneousMatrix mH_left, mH_right; mH_left.init(); mH_right.init();
            double x=0, y=0;
            int l = currentTestPattern.nbX, c = currentTestPattern.nbY, n = currentTestPattern.nbPoints;
            vpRotationMatrix R_left,R_right;
            vpTranslationVector T_left, T_right;
  
            if(currentTestPattern.type==DOT2D || currentTestPattern.type==GRID2D)
            {
               vpPoint pt_left, pt_right;
               pt_left = currentTestPattern.grid.at( 0 ); 
               vpPixelMeterConversion::convertPoint(cam_left, listImage_left[k].at( 0 ), x, y); 
               pt_left.set_x(x); pt_left.set_y(y); pose_left.addPoint(pt_left);
               pt_left = currentTestPattern.grid.at(c-1);
               vpPixelMeterConversion::convertPoint(cam_left, listImage_left[k].at(c-1), x, y); 
               pt_left.set_x(x); pt_left.set_y(y); pose_left.addPoint(pt_left);
               pt_left = currentTestPattern.grid.at(n-l); 
               vpPixelMeterConversion::convertPoint(cam_left, listImage_left[k].at(n-l), x, y); 
               pt_left.set_x(x); pt_left.set_y(y); pose_left.addPoint(pt_left);
               pt_left = currentTestPattern.grid.at(n-1); 
               vpPixelMeterConversion::convertPoint(cam_left, listImage_left[k].at(n-1), x, y); 
               pt_left.set_x(x); pt_left.set_y(y); pose_left.addPoint(pt_left);
               pt_right = currentTestPattern.grid.at( 0 ); 
               vpPixelMeterConversion::convertPoint(cam_right, listImage_right[k].at( 0 ), x, y); 
               pt_right.set_x(x); pt_right.set_y(y); pose_right.addPoint(pt_right);
               pt_right = currentTestPattern.grid.at(c-1); 
               vpPixelMeterConversion::convertPoint(cam_right, listImage_right[k].at(c-1), x, y); 
               pt_right.set_x(x); pt_right.set_y(y); pose_right.addPoint(pt_right);
               pt_right = currentTestPattern.grid.at(n-l); 
               vpPixelMeterConversion::convertPoint(cam_right, listImage_right[k].at(n-l), x, y); 
               pt_right.set_x(x); pt_right.set_y(y); pose_right.addPoint(pt_right);
               pt_right = currentTestPattern.grid.at(n-1); 
               vpPixelMeterConversion::convertPoint(cam_right, listImage_right[k].at(n-1), x, y); 
               pt_right.set_x(x); pt_right.set_y(y); pose_right.addPoint(pt_right);
            }
            else if(currentTestPattern.type==DOT3D)
            {
               for(int i=0;i<6;i++)
               {
                  vpPoint pt_left = currentTestPattern.grid.at(i*2);
                  vpPoint pt_right = currentTestPattern.grid.at(i*2);
                  vpPixelMeterConversion::convertPoint(cam_left, listImage_left[k].at(2*i), x, y);
                  vpPixelMeterConversion::convertPoint(cam_right, listImage_right[k].at(2*i), x, y);
                  pt_left.set_x(x); pt_left.set_y(y); pose_left.addPoint(pt_left);
                  pt_right.set_x(x); pt_right.set_y(y); pose_right.addPoint(pt_right);
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
               case 0: pose_left.computePose(vpPose::LAGRANGE,mH_left);pose_right.computePose(vpPose::LAGRANGE,mH_right); break;
               case 1: pose_left.computePose(vpPose::DEMENTHON,mH_left); pose_right.computePose(vpPose::DEMENTHON,mH_right);break;
               case 2: pose_left.computePose(vpPose::LAGRANGE_LOWE,mH_left);pose_right.computePose(vpPose::LAGRANGE_LOWE,mH_right); break;
               case 3: pose_left.computePose(vpPose::DEMENTHON_LOWE,mH_left); pose_right.computePose(vpPose::DEMENTHON_LOWE,mH_right);break;
               case 4: pose_left.computePose(vpPose::LAGRANGE_VIRTUAL_VS,mH_left); pose_right.computePose(vpPose::LAGRANGE_VIRTUAL_VS,mH_right);break;
               case 5: pose_left.computePose(vpPose::DEMENTHON_VIRTUAL_VS,mH_left);  pose_right.computePose(vpPose::DEMENTHON_VIRTUAL_VS,mH_right);break;
            } 
            homogeneousMatrixTable_left[k] = mH_left;
            homogeneousMatrixTable_right[k] = mH_right;
      }
      /***************/
      /*   A FAIRE   */
      /***************/     
   }
   if(methode == OPENCV)
   {
      int nbPointInImage = currentTestPattern.nbPoints;  
      rotation_matrix = cvCreateMat(3,3,CV_64FC1);
      translation_vector = cvCreateMat(3,1,CV_64FC1);
      CvMat *object_points = cvCreateMat(nbPointInImage*nbImages ,3 ,CV_32FC1);
      CvMat *image_points_left  = cvCreateMat(nbPointInImage*nbImages ,2 ,CV_32FC1);
      CvMat *image_points_right  = cvCreateMat(nbPointInImage*nbImages ,2 ,CV_32FC1);
      CvMat *point_counts  = cvCreateMat(nbImages, 1, CV_32SC1);
      essential = cvCreateMat(3, 3, CV_64F);
      fundamental = cvCreateMat(3, 3, CV_64F);

      for(int k=0;k<nbImages;k++)
      {
         for(int i=0;i<nbPointInImage;i++)
         {
            CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,0) = currentTestPattern.grid.at(i).get_oX(); 
            CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,1) = currentTestPattern.grid.at(i).get_oY();
            CV_MAT_ELEM( *object_points,float,k*nbPointInImage + i,2) = currentTestPattern.grid.at(i).get_oZ();
            CV_MAT_ELEM( *image_points_left, float,k*nbPointInImage + i,0) = listImage_left[k].at(i).get_u();
            CV_MAT_ELEM( *image_points_left, float,k*nbPointInImage + i,1) = listImage_left[k].at(i).get_v();
            CV_MAT_ELEM( *image_points_right, float,k*nbPointInImage + i,0) = listImage_right[k].at(i).get_u();
            CV_MAT_ELEM( *image_points_right, float,k*nbPointInImage + i,1) = listImage_right[k].at(i).get_v();
         }
      }

      cvZero(point_counts);
      cvSet(point_counts,cvScalar(nbPointInImage));
      CvSize image_size = cvSize( width,height);

      float repro_error_stereo = cvStereoCalibrate( object_points, image_points_left, image_points_right, point_counts,
                                    intrinsic_matrix_left, distortion_coeffs_left, intrinsic_matrix_right, distortion_coeffs_right, 
                                    image_size, rotation_matrix, translation_vector, essential, fundamental,
                                    cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, 1e-5),
                                   /* CV_CALIB_SAME_FOCAL_LENGTH +*/ CV_CALIB_FIX_INTRINSIC );

      printf("\nOpenCV Retrojection Error Stereo: %lf pixels\n",repro_error_stereo);

//      printf( "\nrotation vector opencv\n");
//      CvMat *rotation_vector  = cvCreateMat(  3, 1, CV_64FC1);
//      cvRodrigues2(rotation_matrix,rotation_vector);
//      for( size_t i = 0; i < 3; i++ ) 
//         printf( " %.3f ", vpMath::deg(at2(rotation_vector,i,0)));
//      printf( "\n");
//      printf( "\ntranslation vector opencv\n");
//      for( size_t i = 0; i < 3; i++ ) 
//         printf( " %.3f ",at2(translation_vector,i,0));
//      printf( "\n\n");

//      calibrationCheckStereo(nbImages);

      CvMat *_Q =  cvCreateMat(4, 4, CV_64F);
      CvMat *intrinsic_matrix_left_rectify = cvCreateMat(3, 4, CV_64F);
      CvMat *intrinsic_matrix_right_rectify = cvCreateMat(3, 4, CV_64F);
      CvMat *rotation_matrix_left = cvCreateMat(3,3,CV_64F);
      CvMat *rotation_matrix_right = cvCreateMat(3,3,CV_64F);

      cvStereoRectify(intrinsic_matrix_left, intrinsic_matrix_right, 
                      distortion_coeffs_left, distortion_coeffs_right, 
                      image_size, rotation_matrix, translation_vector, 
                      rotation_matrix_left, rotation_matrix_right, intrinsic_matrix_left_rectify, intrinsic_matrix_right_rectify, _Q, /*0*/CV_CALIB_ZERO_DISPARITY );

      if(m_save == true)
      {
         filename = repertoire_extrinsic + "extrinsics-" + m_camera_left + "-" + m_camera_right + ".xml";
         FileStorage fs(filename, CV_STORAGE_WRITE);
         if( fs.isOpened() )
         {
            fs << "F" << fundamental << "E" <<  essential
               << "R_left" << rotation_matrix_left << "R_right" << rotation_matrix_right
               << "P_left" << intrinsic_matrix_left_rectify << "P_right" << intrinsic_matrix_left_rectify
               << "Q" << _Q
               << "R" << rotation_matrix << "T" << translation_vector;
            fs.release();
         }
         else
            cout << "Error: can not save the extrinsic parameters\n";
      }
   }
   return 1;
}

/**
* retroprojectionStereo
 * @fn vector<vpImagePoint> calibrage::retroprojectionStereo(vector<vpPoint>pt3D, int nbImages, string method, int leftorright, bool withDistortion)
 * @brief computes the retroprojection
 * @details Need : list of 3D points coordinates of the testpattern, the images number for images
 * 2 methods are available : "opencv" and "visp"
 * 2 options are available : withDistortion = true (default), withDistortion = false
 * Set leftorright = 0 for left camera, leftorright = 1 for right camera
 *\n
 * @param pt3D, nbImages, method, leftorright, withDistortion
 * @return a list of 2D vpImagePoint
*/
vector<vpImagePoint> calibrage::retroprojectionStereo(vector<vpPoint>pt3D, int nbImages, string method, int leftorright, bool withDistortion)
{
   vector<vpImagePoint> ptProjImage_left, ptProjImage_right, null;
   if(method == "opencv")
   {
      CvMat *object_points = cvCreateMat(currentTestPattern.nbPoints ,3 ,CV_32FC1);
      CvMat *image_points_left = cvCreateMat(currentTestPattern.nbPoints ,2 ,CV_32FC1);
      CvMat *rotation_left = cvCreateMat(1,3,CV_32FC1);
      CvMat *translation_left = cvCreateMat(1,3,CV_32FC1);
      CvMat *image_points_right = cvCreateMat(currentTestPattern.nbPoints ,2 ,CV_32FC1);
      CvMat *rotation_right = cvCreateMat(1,3,CV_32FC1);
      CvMat *translation_right = cvCreateMat(1,3,CV_32FC1);

      for(int k=0;k<nbImages;k++)
      {
         for(unsigned int i=0;i<pt3D.size();i++)
         {
            CV_MAT_ELEM( *object_points,float,i,0) = pt3D.at(i).get_X();
            CV_MAT_ELEM( *object_points,float,i,1) = pt3D.at(i).get_Y();
            CV_MAT_ELEM( *object_points,float,i,2) = pt3D.at(i).get_Z();
         }
         cvGetRow(rotation_vector_left,rotation_left,k);
         cvGetRow(translation_vector_left,translation_left,k);
         cvProjectPoints2(object_points,rotation_left,translation_left,intrinsic_matrix_left,distortion_coeffs_left,image_points_left);
         cvGetRow(rotation_vector_right,rotation_right,k);
         cvGetRow(translation_vector_right,translation_right,k);
         cvProjectPoints2(object_points,rotation_right,translation_right,intrinsic_matrix_right,distortion_coeffs_right,image_points_right);

         for(int i=0;i<image_points_left->rows;i++)
         {
            vpImagePoint pt(CV_MAT_ELEM( *image_points_left,float,i,1),CV_MAT_ELEM( *image_points_left,float,i,0));
            ptProjImage_left.push_back( pt );
         }
         for(int i=0;i<image_points_right->rows;i++)
         {
            vpImagePoint pt(CV_MAT_ELEM( *image_points_right,float,i,1),CV_MAT_ELEM( *image_points_right,float,i,0));
            ptProjImage_right.push_back( pt );
         }
      }
   }
   if(method == "visp")
   {
      for(int k=0;k<nbImages;k++)
      {
         for(unsigned int i=0; i<pt3D.size();i++)
         {
            vpPoint pt_left = pt3D.at(i);
            vpPoint pt_right = pt3D.at(i);
            pt_left.project(homogeneousMatrixTable_left[k]);
            pt_right.project(homogeneousMatrixTable_right[k]);
            vpImagePoint imagePt_left, imagePt_right;
            if(withDistortion)
            {
               vpMeterPixelConversion::convertPointWithDistortion(cam_left,pt_left.p[0],pt_left.p[1],imagePt_left);
               vpMeterPixelConversion::convertPointWithDistortion(cam_right,pt_right.p[0],pt_right.p[1],imagePt_right);
            }
            else
            {
               vpMeterPixelConversion::convertPointWithoutDistortion(cam_left,pt_left.p[0],pt_left.p[1],imagePt_left);
               vpMeterPixelConversion::convertPointWithoutDistortion(cam_right,pt_right.p[0],pt_right.p[1],imagePt_right);
            }
            ptProjImage_left.push_back(imagePt_left);
            ptProjImage_right.push_back(imagePt_right);
         }
      }
   }
   if(leftorright==0)
      return ptProjImage_left;
   else if(leftorright==1)
      return ptProjImage_right;

   return null;
}

/**
* showRetroprojectionStereo
 * @fn void calibrage::showRetroprojectionStereo(vpImage<unsigned char> &image_left, vpImage<unsigned char> &image_right, int methode, int nbImages)
 * @brief compute and draw the retroprojection in external window
 *\n
 * @param image_left, image_right, methode, nbImages
*/
void calibrage::showRetroprojectionStereo(vpImage<unsigned char> &image_left, vpImage<unsigned char> &image_right, int methode, int nbImages)
{
   char comment[FILENAME_MAX];
   vpDisplayOpenCV displayRetro_left,displayRetro_right;
   filename_left = m_imageFilenames_1.at(0);
   filename_right = m_imageFilenames_2.at(0);
   vpImageIo::read(image_left, filename_left);
   vpImageIo::read(image_right, filename_right);
   displayRetro_left.init(image_left,100,200,"Retroprojection left");
   displayRetro_right.init(image_right,image_left.getWidth()+100,200,"Retroprojection right");

   if(!poseEstimationStereo(methode, nbImages,image_left.getWidth(),image_left.getHeight())) 
   {
      cout << "Error during Estimation" << endl; 
      return; 
   }

   vector<vpImagePoint> retroprojPointsViSP_left, retroprojPointsViSPwithoutDist_left, retroprojPointsOpenCV_left;
   vector<vpImagePoint> retroprojPointsViSP_right, retroprojPointsViSPwithoutDist_right, retroprojPointsOpenCV_right;
   vector<vpImagePoint> imagePoints_left; imagePoints_left.clear();
   vector<vpImagePoint> imagePoints_right; imagePoints_right.clear();
   for(int k=0; k<nbImages;k++)
   {
      for(unsigned int i=0; i<listImage_left[k].size();i++)
         imagePoints_left.push_back(listImage_left[k].at(i));
      for(unsigned int i=0; i<listImage_right[k].size();i++)
         imagePoints_right.push_back(listImage_right[k].at(i));
   }

   if(methode == VISP)
   {
      retroprojPointsViSPwithoutDist_left = retroprojectionStereo(currentTestPattern.grid,nbImages,"visp",0,false); //without distortion
      float retroprojErrorViSPwithoutDist_left = computeRetroprojectionError(retroprojPointsViSPwithoutDist_left,imagePoints_left);
      cout << "Visp Retrojection Error without distortion left : " << retroprojErrorViSPwithoutDist_left << " pixels / image"<< endl;
      retroprojPointsViSPwithoutDist_right = retroprojectionStereo(currentTestPattern.grid,nbImages,"visp",1,false); //without distortion
      float retroprojErrorViSPwithoutDist_right = computeRetroprojectionError(retroprojPointsViSPwithoutDist_right,imagePoints_right);
      cout << "Visp Retrojection Error without distortion right : " << retroprojErrorViSPwithoutDist_right << " pixels / image\n"<< endl;
   }
   if(methode == VISP_DIST)
   {
      retroprojPointsViSP_left = retroprojectionStereo(currentTestPattern.grid,nbImages,"visp",0);
      float retroprojErrorViSPwithDist_left = computeRetroprojectionError(retroprojPointsViSP_left,imagePoints_left);
      cout << "Visp Retrojection Error left:   " << retroprojErrorViSPwithDist_left << " pixels / image" << endl;
      retroprojPointsViSP_right = retroprojectionStereo(currentTestPattern.grid,nbImages,"visp",1);
      float retroprojErrorViSPwithDist_right = computeRetroprojectionError(retroprojPointsViSP_right,imagePoints_right);
      cout << "Visp Retrojection Error right:   " << retroprojErrorViSPwithDist_right << " pixels / image\n" << endl;
   }
   if(methode == OPENCV)
   {
      retroprojPointsOpenCV_left = retroprojectionStereo(currentTestPattern.grid,nbImages,"opencv",0);
      float retroprojErrorOpenCV_left = computeRetroprojectionError(retroprojPointsOpenCV_left,imagePoints_left);
      cout << "OpenCV Retrojection Error left: " << retroprojErrorOpenCV_left << " pixels" << endl;// / image" << endl;
      retroprojPointsOpenCV_right = retroprojectionStereo(currentTestPattern.grid,nbImages,"opencv",1);
      float retroprojErrorOpenCV_right = computeRetroprojectionError(retroprojPointsOpenCV_right,imagePoints_right);
      cout << "OpenCV Retrojection Error right: " << retroprojErrorOpenCV_right << " pixels" << endl;// / image\n" << endl;
   }

   //DISPLAY ERROR
   int check = 0;
   for(int k=0;k<m_nimages;k++)
   {
      if(validImage[k]==1)
      {
         int n = currentTestPattern.nbPoints;
         filename_left = m_imageFilenames_1.at(k);
         filename_right = m_imageFilenames_2.at(k);
         vpImageIo::read(image_left,filename_left);
         vpImageIo::read(image_right,filename_right);
         vpDisplay::display(image_left);
         vpDisplay::display(image_right);

         for(int i=0;i<currentTestPattern.nbPoints;i++)
         {
            vpDisplay::displayCross(image_left,imagePoints_left.at(i+check*n),10,vpColor::green,2);
            vpDisplay::displayCross(image_right,imagePoints_right.at(i+check*n),10,vpColor::green,2);
            if(methode == VISP)
            {
               vpDisplay::displayCross(image_left,retroprojPointsViSPwithoutDist_left.at(i+check*n),10,vpColor::blue,1);
               vpDisplay::displayCross(image_right,retroprojPointsViSPwithoutDist_right.at(i+check*n),10,vpColor::blue,1);
            }
            else if(methode == VISP_DIST)
            {
               vpDisplay::displayCross(image_left,retroprojPointsViSP_left.at(i+check*n),10,vpColor::blue,1);
               vpDisplay::displayCross(image_right,retroprojPointsViSP_right.at(i+check*n),10,vpColor::blue,1);
            }
            else if(methode == OPENCV)
            {
               vpDisplay::displayCross(image_left,retroprojPointsOpenCV_left.at(i+check*n),10,vpColor::blue,1);
               vpDisplay::displayCross(image_right,retroprojPointsOpenCV_right.at(i+check*n),10,vpColor::blue,1);
            }  
         }
         vpDisplay::displayCharString(image_left,10,10,"Base points",vpColor::green);
         vpDisplay::displayCharString(image_right,10,10,"Base points",vpColor::green);
         vpDisplay::displayCharString(image_left, image_left.getHeight() -15, 10,filename_left.c_str(),vpColor::orange);
         vpDisplay::displayCharString(image_right, image_right.getHeight() -15, 10,filename_right.c_str(),vpColor::orange);
         if(methode == VISP)
         {
            sprintf(comment,"Visp projection without distortion left %lf pixels",computeRetroprojectionError(retroprojPointsViSPwithoutDist_left,imagePoints_left,check*n,(check+1)*n));
            vpDisplay::displayCharString(image_left,20,10,&comment[0],vpColor::blue);
            sprintf(comment,"Visp projection without distortion right %lf pixels",computeRetroprojectionError(retroprojPointsViSPwithoutDist_right,imagePoints_right,check*n,(check+1)*n));
            vpDisplay::displayCharString(image_right,20,10,&comment[0],vpColor::blue);
         }
         else if(methode == VISP_DIST)
         {
            sprintf(comment,"Visp projection left %lf pixel",computeRetroprojectionError(retroprojPointsViSP_left,imagePoints_left,check*n,(check+1)*n));
            vpDisplay::displayCharString(image_left,30,10,&comment[0],vpColor::blue);
            sprintf(comment,"Visp projection right %lf pixel",computeRetroprojectionError(retroprojPointsViSP_right,imagePoints_right,check*n,(check+1)*n));
            vpDisplay::displayCharString(image_right,30,10,&comment[0],vpColor::blue);
         }
         else if(methode == OPENCV)
         {
            sprintf(comment,"OpenCV projection left %lf pixels",computeRetroprojectionError(retroprojPointsOpenCV_left,imagePoints_left,check*n,(check+1)*n));
            vpDisplay::displayCharString(image_left,40,10,&comment[0],vpColor::blue);
            sprintf(comment,"OpenCV projection right %lf pixels",computeRetroprojectionError(retroprojPointsOpenCV_right,imagePoints_right,check*n,(check+1)*n));
            vpDisplay::displayCharString(image_right,40,10,&comment[0],vpColor::blue);
         }
         check++;
         vpDisplay::flush(image_left);
         vpDisplay::flush(image_right);
         if(m_click)
         {
            bool isover = false;
            while(!isover)
               if(vpDisplay::getClick(image_left, false)||vpDisplay::getClick(image_right, false))
                  isover = true;
         }
      }
   }
   vpDisplay::close(image_left);
   vpDisplay::close(image_right);
}

/**
* modeStereo
 * @fn int calibrage::modeStereo()
 * @brief Calibration program for stereo camera
 * @details Calibration program for stereo camera
 *\n
 * @return 0
*/
int calibrage::modeStereo()
{ 
   vpDisplayOpenCV display_right, display_left;   
     
   if(!defPattern("./../data/mire.cfg"))
      return 0;

   if(!loadImageStereo(I_left, I_right))
      return 0;
                            
   table_cal_left = new vpCalibration[m_nimages]; //coordinates tab : [X, Y, Z, u, v]
   table_cal_right = new vpCalibration[m_nimages]; 
   listImage_left = new vector<vpImagePoint>[m_nimages];
   listImage_right = new vector<vpImagePoint>[m_nimages];

   // read the image
   filename_left = m_imageFilenames_1.at(iter);
   filename_right = m_imageFilenames_2.at(iter);
   vpImageIo::read(I_left, filename_left);
   vpImageIo::read(I_right, filename_right);
   display_left.init(I_left,100,200,"Calibration left");
   display_right.init(I_right,I_left.getWidth()+100,200,"Calibration right");

   //Initialisation of camera parameters
   //Initial camera parameters have to be close of real camera parameters
   cam_right.initPersProjWithDistortion(Focal,Focal,I_left.getWidth()/2,I_left.getHeight()/2,0,0);
   cam_left.initPersProjWithDistortion(Focal,Focal,I_right.getWidth()/2,I_right.getHeight()/2,0,0);

   while (iter < m_nimages) 
   {
      try
      {
         filename_left = m_imageFilenames_1.at(iter);
         filename_right = m_imageFilenames_2.at(iter);
         std::string::size_type found = m_imageFilenames_1.at(0).find_last_of("/\\");
         std::string::size_type found2 = m_imageFilenames_1.at(0).find_last_of(".");
         string checkFile_left = repertoire_calibtab + m_imageFilenames_1.at(iter).substr(found+1,found2-found-1) + ".txt";

         found = m_imageFilenames_2.at(0).find_last_of("/\\");
         found2 = m_imageFilenames_2.at(0).find_last_of(".");
         string checkFile_right = repertoire_calibtab + m_imageFilenames_2.at(iter).substr(found+1,found2-found-1) + ".txt";

         cout << "#INFO: read : " << m_imageFilenames_1.at(iter).substr(found+1,found2) << " and " << m_imageFilenames_2.at(iter).substr(found+1,found2) <<endl;
         fflush(stdout);
         vpImageIo::read(I_left, filename_left);
         vpImageIo::read(I_right, filename_right);
         vpDisplay::display(I_left);vpDisplay::flush(I_left) ;
         vpDisplay::display(I_right);vpDisplay::flush(I_right) ;

         int nbPointsTotal = currentTestPattern.nbPoints;
         vpImagePoint l[nbPointsTotal],r[nbPointsTotal];

         if(!loadCalibTab(checkFile_left,l))
            if(!findImagePoints(I_left, l,filename_left))
               continue;
         displayPoints(I_left, l, nbPointsTotal,filename_left);

         if(!loadCalibTab(checkFile_right,r))
            if(!findImagePoints(I_right, r,filename_right)) 
               continue;

         if((l[0].get_u() - l[nbPointsTotal-1].get_u())*(r[0].get_u() - r[nbPointsTotal-1].get_u()) < 0||
               (l[0].get_v() - l[nbPointsTotal-1].get_v())*(r[0].get_v() - r[nbPointsTotal-1].get_v()) < 0 )
         {
            cout<<"   Bad Pattern Detection -> pose ignored"<<endl;
            cout<<endl;
            iter++;
            niter++;
            continue;
         }
         displayPoints(I_right, r, nbPointsTotal,filename_right);

         validatePoseStereo(I_left, I_right, l, r, nbPointsTotal);
      }
      catch(...){return(-1);}
      iter++;
   }
   display_right.close(I_right);
   display_left.close(I_left);

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

   //Launch calibration
   calibrateStereo(I_left,OPENCV,nbImgCal);

   printf( "%s:\n",m_camera_left.c_str());
   printf( "Intrinsic matrix for opencv calibration :\n");
   for( size_t i = 0; i < 3; i++ ) 
   {
      for( size_t j = 0; j < 3; j++ ) 
         // Observe the type used in the template
         printf( " %.6f ", at(intrinsic_matrix_left,i,j));
      printf( "\n");
   }
   printf( "distortion coeffs for opencv calibration :\n");
   for( size_t j = 0; j < 5; j++ )
      // Observe the type used in the template
      printf( " %.6f ", at(distortion_coeffs_left,0,j));
   printf("\n\n");
   printf( "%s:\n",m_camera_right.c_str());
   printf( "Intrinsic matrix for opencv calibration :\n");
   for( size_t i = 0; i < 3; i++ ) 
   {
      for( size_t j = 0; j < 3; j++ ) 
         // Observe the type used in the template
         printf( " %.6f ", at(intrinsic_matrix_right,i,j));
      printf( "\n");
   }
   printf( "distortion coeffs for opencv calibration :\n");
   for( size_t j = 0; j < 5; j++ )
      // Observe the type used in the template
      printf( " %.6f ", at(distortion_coeffs_right,0,j));
   printf("\n\n");

   showRetroprojectionStereo(I_left, I_right, OPENCV,nbImgCal);

   printf( "\nrotation vector opencv (degrees) :\n");
   CvMat *rotation_vector  = cvCreateMat(  3, 1, CV_64FC1);
   cvRodrigues2(rotation_matrix,rotation_vector);
   for( size_t i = 0; i < 3; i++ ) 
      printf( " %.3f ", vpMath::deg(at2(rotation_vector,i,0)));
   printf( "\n");
   printf( "\ntranslation vector opencv (m) :\n");
   for( size_t i = 0; i < 3; i++ ) 
      printf( " %.3f ",at2(translation_vector,i,0));

   printf( "\n\n");

   return 0;
}

/**
* calibrationCheckStereo
 * @fn void calibrage::calibrationCheckStereo(int nbImages)
 * @brief Check the Calibration quality
 *\n
*/
void calibrage::calibrationCheckStereo(int nbImages)
{
      int nbPointInImage = currentTestPattern.nbPoints;  
      // CALIBRATION QUALITY CHECK
      // because the output fundamental matrix implicitly
      // includes all the output information,
      // we can check the quality of calibration using the
      // epipolar geometry constraint: m2^t*F*m1=0
      vector<CvPoint3D32f> lines[2];
      vector<CvPoint2D32f> points[2];
      CvMat *image_points_left  = cvCreateMat(nbPointInImage*nbImages ,2 ,CV_32FC1);
      CvMat *image_points_right  = cvCreateMat(nbPointInImage*nbImages ,2 ,CV_32FC1);
      points[0].resize(nbPointInImage*nbImages);
      points[1].resize(nbPointInImage*nbImages);
      for(int k=0;k<nbImages;k++)
      {
         for(int i=0;i<nbPointInImage;i++)
         {
            points[0][k*nbPointInImage + i].x=listImage_left[k].at(i).get_u();
            points[0][k*nbPointInImage + i].y=listImage_left[k].at(i).get_v();
            points[1][k*nbPointInImage + i].x=listImage_right[k].at(i).get_u();
            points[1][k*nbPointInImage + i].y=listImage_right[k].at(i).get_v();
         }
      }
      *image_points_left = cvMat(1,nbPointInImage*nbImages ,CV_32FC2, &points[0][0]);
      *image_points_right = cvMat(1,nbPointInImage*nbImages ,CV_32FC2, &points[1][0] );
      lines[0].resize(nbPointInImage*nbImages);
      lines[1].resize(nbPointInImage*nbImages);
      CvMat _L1 = cvMat(1,nbPointInImage*nbImages , CV_32FC3, &lines[0][0]);
      CvMat _L2 = cvMat(1,nbPointInImage*nbImages , CV_32FC3, &lines[1][0]);
      //Always work in undistorted space
      cvUndistortPoints( image_points_left, image_points_left, intrinsic_matrix_left, distortion_coeffs_left, 0, intrinsic_matrix_left);
      cvUndistortPoints( image_points_right,image_points_right, intrinsic_matrix_right, distortion_coeffs_right, 0, intrinsic_matrix_right);
      cvComputeCorrespondEpilines( image_points_left, 1, fundamental, &_L1 );
      cvComputeCorrespondEpilines( image_points_right, 2, fundamental, &_L2 );
      double avgErr = 0;
      for( int i = 0; i < nbPointInImage*nbImages; i++ )
      {
         double err = fabs(points[0][i].x*lines[1][i].x + points[0][i].y*lines[1][i].y + lines[1][i].z) +
                      fabs(points[1][i].x*lines[0][i].x + points[1][i].y*lines[0][i].y + lines[0][i].z);
         avgErr += err;
      }
      printf( "avg_repro_err  = %g\n", avgErr/(nbImages*nbPointInImage));
}
