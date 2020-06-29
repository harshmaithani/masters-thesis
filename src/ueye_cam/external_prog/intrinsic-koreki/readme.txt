Installation process to allow the use of Calibration_intrinsic-koreki

(1) Install essential packages
#First, do: 

sudo apt-get install build-essential
sudo apt-get install cmake-curses-gui

####################################
#############   VISP   #############
####################################

(2) Install ViSP
#ViSP must be install on the computer. The program is tested with VISP-2.8.0 version.
#ViSP-2.8.0.zip archive can be found in */projet/data/3rdparty. If ViSP is already install, go to the next step. Otherwise, do:

sudo apt-get install libx11-dev liblapack-dev libv4l-dev libdc1394-22-dev libxml2-dev
sudo apt-get install libpng12-dev libjpeg-dev
sudo apt-get install libswscale-dev libavutil-dev libavformat-dev libavcodec-dev libbz2-dev libbz2-1.0
sudo apt-get install libopencv-dev
sudo apt-get install freenect libusb-1.0-0-dev

#Create a directory where you want to build ViSP:

mkdir ViSP
cd ViSP
unzip ../ViSP-2.8.0.zip

#Build ViSP:

mkdir ViSP-2.8.0/build
cd ViSP-2.8.0/build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install

###############################################
#############   TROUBLESHOOTING   #############
###############################################

#I encounter some issues with libexpat: the libexpat.so.0 was not found. But libexpat.so.1 should exist in a lib directory. For me, it was in /lib/x86_64-linux-gnu. #Then:

cd /lib/x86_64-linux-gnu
sudo ln libexpat.so.1 libexpat.so.0
#The project should work now.

