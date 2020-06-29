/**
 * \file calibrage.h
 *
 * \brief <b>Header file for the class calibrage</b>
 *
 * \details The class calibrage provides all the fonctions need to compute a 
 * mono camera calibration or a stereo camera calibration.
 * \n
 * \date september 2013
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

#ifndef CALIBRAGE_H
#define CALIBRAGE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

#include <visp/vpCalibration.h>
#include <visp/vpDisplayX.h>
#include <visp/vpIoTools.h>
#include <visp/vpVideoReader.h> 
#include <visp/vpXmlParserCamera.h>
#include <visp/vpPose.h>
#include <visp/vpDot2.h>
#include <visp/vpPixelMeterConversion.h>
#include <visp/vpMeterPixelConversion.h>
#include <visp/vpDisplayOpenCV.h>
#include <visp/vpOpenCVGrabber.h>
#include <visp/vpV4l2Grabber.h>

#include <opencv2/opencv.hpp>

#define VISP  0   /** ViSP calibration without distortion */
#define VISP_DIST  1 /** ViSP calibration with distortion */
#define OPENCV 2  /** OpenCV calibration */

using namespace cv;
using namespace std;

enum Pattern_type {GRID2D, DOT2D, DOT3D};
      
struct testPattern
{
   Pattern_type type;
   int nbPoints;
   int nbX;
   int nbY;
   int nbZ;
   float dx;
   float dy;
   float dz;
   float bias;
   vector<vpPoint> gridToTrack;
   vector<vpPoint> grid;
};

/**
 * calibrage Class header
*/
class calibrage
{
   public:
      calibrage(std::string name, std::vector<std::string> imageFilenames_1, bool click, bool save, std::string cameraType, bool useOpenCV);
      calibrage(std::string namel, std::string namer, std::vector<std::string> imageFilenames_1, std::vector<std::string> imageFilenames_2, bool click, bool save, std::string cameraType, bool useOpenCV);
      ~calibrage();

	/** public method */
		/* common.cpp */
      bool readPattern(const string &cfgfile);  // Read the pattern configuration file
      bool defPattern(const string &cfgfile);   // apply pattern parameters
      bool loadCalibTab(string name, vpImagePoint pt[]);

		/* calibrage.cpp */
      int modeMono();
      bool loadImage(vpImage<unsigned char> image);

		/* calibrageStereo.cpp */
      int modeStereo();
      bool loadImageStereo(vpImage<unsigned char> image_left, vpImage<unsigned char> image_right);
      void calibrationCheckStereo(int nbImages);

   /** Operation on matrix */
      float at(CvMat *mat, int i, int j) { return CV_MAT_ELEM( *mat,float,i,j);}
      float at(CvMat *mat, int i) { if(mat->cols==1) return CV_MAT_ELEM( *mat,float,i,0); else return CV_MAT_ELEM( *mat,float,0,i);}
      double at2(CvMat *mat, int i, int j) { return CV_MAT_ELEM( *mat,double,i,j);}
      double at2(CvMat *mat, int i) { if(mat->cols==1) return CV_MAT_ELEM( *mat,double,i,0); else return CV_MAT_ELEM( *mat,double,0,i);}

	/** public variables */
      /* intrinsic estimate */
      double Focal;

      /** pattern parameters */
      Size boardSize;         // The size of the board -> Number of items by width and height
      double boardSizedepth;  // The size of the board -> Number of items in depth
      double squareSize_X;    // The size of a square in your defined unit (point, millimeter,etc)
      double squareSize_Y;
      double squareSize_Z;
      double BIAS;
      string patternToUse; // The pattern kind (chessboard or circles grid)

      /** Camera names */
      string m_camera;
      string m_camera_left;
      string m_camera_right;
      string filename;
      string filename_left;
      string filename_right;

      /** data path */
      string repertoire_calibtab;
      string repertoire_extrinsic;
      string repertoire_intrinsic;

      bool m_useOpenCV;
      bool m_save;    // First image
      bool m_click;  // number of image's load (>= 2)
      int m_nimages;  // number of image's load (>= 2)
      int iter;
      int niter;
      int nbImgCal;  // number of image use for calibration
      int validImage[1000];

      std::vector<std::string> m_imageFilenames_1;
      std::vector<std::string> m_imageFilenames_2;

 
   protected:
      /** Create vpPoint */
      vpPoint create_vpPoint(double oX, double oY, double oZ, double x=0, double y=0) { vpPoint pt; pt.setWorldCoordinates(oX,oY,oZ); pt.set_X(oX); pt.set_Y(oY); pt.set_Z(oZ); pt.set_x(x); pt.set_y(y); return pt;}

      /** Create Pattern */
      void setPatternParam(testPattern *m, int nbX, int nbY, float dx, float dy) { setPatternParam(m,nbX,nbY,0,dx,dy,0,0);}
      void setPatternParam(testPattern *m, int nbX, int nbY, int nbZ, float dx, float dy, float dz, float bias) { m->nbPoints = nbX*nbY + nbX*nbZ + nbY*nbZ; m->nbX = nbX; m->nbY = nbY; m->nbZ = nbZ; m->dx = dx; m->dy = dy; m->dz = dz; m->bias = bias;}
      void setPatternParam(testPattern *m, vector<vpPoint> grid, vector<vpPoint> gridToTrack) { m->grid = grid; m->gridToTrack = gridToTrack;}
      void setPatternParam(testPattern *m, vector<vpPoint> grid) { m->grid = grid; m->gridToTrack = grid;}

      /** ViSP parameters and fonctions */
         /** parameters */
         testPattern currentTestPattern;
         vpCalibration *table_cal;
         vpCalibration *table_cal_left;
         vpCalibration *table_cal_right;
         vpImage<unsigned char> imageViSP; 
         vpImage<unsigned char> I_left;
         vpImage<unsigned char> I_right;
         vpCameraParameters cam;
         vpCameraParameters cam_left;
         vpCameraParameters cam_right;
         vector<vpImagePoint> *listImage;
         vector<vpImagePoint> *listImage_left;
         vector<vpImagePoint> *listImage_right;
         vpHomogeneousMatrix *homogeneousMatrixTable;
         vpHomogeneousMatrix *homogeneousMatrixTable_left;
         vpHomogeneousMatrix *homogeneousMatrixTable_right;
         /** method */
         int computeCalibrationViSP(vpCalibration::vpCalibrationMethodType methode);
         int computeCalibrationViSPStereo(vpCalibration::vpCalibrationMethodType methode);

      /** opencv parameters and fonctions */
         /** parameters */
         CvMat *distortion_coeffs;
         CvMat *distortion_coeffs_left;
         CvMat *distortion_coeffs_right;
         CvMat *rotation_vector;
         CvMat *rotation_vector_left;
         CvMat *rotation_vector_right;
         CvMat *rotation_matrix;
         CvMat *translation_vector;
         CvMat *translation_vector_left;
         CvMat *translation_vector_right;
         CvMat *intrinsic_matrix;
         CvMat *intrinsic_matrix_left;
         CvMat *intrinsic_matrix_right;
         CvMat *essential;
         CvMat *fundamental;
         /** method */
         float computeOpenCV(int nbImages, int width, int height);
         float computeOpenCVStereo(int nbImages, int width, int height);
      
      /** intrinsec parameters */
      void calibrate(vpImage<unsigned char> &image, int methode, int nbImages);
      void calibrateStereo(vpImage<unsigned char> &image, int methode, int nbImages);

      /** extrinsic parameters */
      vector<vpImagePoint> retroprojection(vector<vpPoint> pt3D, int nbImages, string method, bool withDistortion = true);
      vector<vpImagePoint> retroprojectionStereo(vector<vpPoint>pt3D, int nbImages, string method, int leftorright, bool withDistortion = true);
      void showRetroprojection(vpImage<unsigned char> &image, int methode, int nbImages);
      void showRetroprojectionStereo(vpImage<unsigned char> &image_left, vpImage<unsigned char> &image_right, int methode, int nbImages);
      int poseEstimation(int methode, int nbImages);
      int poseEstimationStereo(int methode, int nbImages, int width, int height);
      float computeRetroprojectionError(vector<vpImagePoint>list1, vector<vpImagePoint>list2, int begin=0, int end=0);

      /** find points */
      void displayPoints(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsTotal, string name);
      bool findImagePoints(vpImage<unsigned char> &image, vpImagePoint pt[], string name);
      bool validatePose(vpImage<unsigned char> &image, vpImagePoint pt[], int nbPointsTotal);
      bool validatePoseStereo(vpImage<unsigned char> &image_left, vpImage<unsigned char> &image_right, vpImagePoint pt_left[], vpImagePoint pt_right[], int nbPointsTotal);
         /** dots */
         bool findDotAuto(vpImage<unsigned char> &image, vpImagePoint pt[]);
         bool findDots(vpImage<unsigned char> &image, vpImagePoint pt[], int nb, string name);
         /** cross */
         bool findGridAuto(vpImage<unsigned char> &image, vpImagePoint pt[]);                                              
         bool findCross(vpImage<unsigned char> &image, vpImagePoint pt[], int nb, string name);
         void findSubCorner(vpImage<unsigned char> &image, vpImagePoint *pt, int size = 9);   

};
#endif // CALIBRAGE_H
