#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <boost/concept_check.hpp>
#include <opencv2/opencv.hpp>


using namespace cv;



vector<Point3f> GenerateCheckBoardPoints()
{
   vector<Point3f> points;
 
      for( int i = 0; i < 8; i++ )
         for( int j = 0; j < 5; j++ )
            points.push_back(Point3f(float(j*0.1), float(i*0.1), 0));

  return points;
}

bool loadIntrinsicFromYAML(const std::string& filename, Mat& M, Mat& D)
{
   FileStorage fs(filename, FileStorage::READ);
   fs["camera_matrix"] >> M;
   fs["distortion_coefficients"] >> D;
   fs.release();
   return true;
}


int main(int argc, char** argv)
{
    Mat img,gray, cameraMatrix_front, distCoeffs_front, cameraMatrix_back, distCoeffs_back, rvec_front, tvec_front ,rmat_front, rvec_back, tvec_back ,rmat_back;
    Mat Transformation_back = Mat::eye(4,4,CV_64F);
    Mat Transformation_front = Mat::eye(4,4,CV_64F);
    Mat Transformation = Mat::eye(4,4,CV_64F);
    
    std::cout<<"load param files"<<std::endl;
    FileStorage fs_front(argv[3], FileStorage::READ);
    fs_front["camera_matrix"] >> cameraMatrix_front;
    fs_front["distortion_coefficients"] >> distCoeffs_front;
    fs_front.release();
    
    FileStorage fs_back(argv[4], FileStorage::READ);
    fs_back["camera_matrix"] >> cameraMatrix_back;
    fs_back["distortion_coefficients"] >> distCoeffs_back;
    fs_back.release();   
    
    
    FileStorage fs_out(argv[5], FileStorage::WRITE);
    
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------process front camera-------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------------------------*/    
    img = imread( argv[1], 1 );
    cvtColor( img, gray, CV_BGR2GRAY );
    Size patternSize = cvSize(8,5);
    vector<Point2f> corners; 

    bool patternfound = findChessboardCorners(gray,patternSize,corners,CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
    
    if(patternfound){
      std::cout<<"chessboard detected"<<std::endl;
      //std::cout<<corners<<std::endl;
      cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
      std::cout<<"corners = "<< corners<<std::endl;
      drawChessboardCorners(gray, patternSize, Mat(corners), patternfound);
      solvePnP(GenerateCheckBoardPoints(), corners, cameraMatrix_front, distCoeffs_front, rvec_front, tvec_front);
      Rodrigues(rvec_front ,rmat_front);
      std::cout<<"Rvec_front = "<<rvec_front<<std::endl;
      std::cout<<"R_front = "<<rmat_front<<std::endl;
      std::cout<<"T_front = "<<tvec_front<<std::endl;
    }
    else std::cout<<"no chessboard detected"<<std::endl;
    namedWindow( "circles", 1 );
    imshow( "circles", gray );
    waitKey(0);
    
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------process back camera--------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    img = imread( argv[2], 1 );
    cvtColor( img, gray, CV_BGR2GRAY );

    patternfound = findChessboardCorners(gray,patternSize,corners,CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
    
    if(patternfound){
      std::cout<<"chessboard detected"<<std::endl;
      //std::cout<<corners<<std::endl;
      cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
      std::cout<<"corners = "<< corners<<std::endl;
      drawChessboardCorners(gray, patternSize, Mat(corners), patternfound);
      solvePnP(GenerateCheckBoardPoints(), corners, cameraMatrix_back, distCoeffs_back, rvec_back, tvec_back);
      Rodrigues(rvec_back ,rmat_back);
      std::cout<<"Rvec_back = "<<rvec_back<<std::endl;
      std::cout<<"R_back = "<<rmat_back<<std::endl;
      std::cout<<"T_back = "<<tvec_back<<std::endl;
    }
    else std::cout<<"no chessboard detected"<<std::endl;
    
    hconcat(rmat_back,tvec_back,Transformation_back);
    Mat temp = (Mat_<double>(1,4) << 0, 0, 0, 1);
    vconcat(Transformation_back,temp,Transformation_back);
    
    hconcat(rmat_front,tvec_front,Transformation_front);
    vconcat(Transformation_front,temp,Transformation_front);
    
    Transformation = Transformation_back * Transformation_front.inv();
    std::cout<<Transformation<<std::endl;
    
//     write result in output file
    fs_out << "Transformation" << Transformation;
    fs_out.release();
    namedWindow( "circles", 1 );
    imshow( "circles", gray );
    waitKey(0);
    
    
    
    return 0;
}
