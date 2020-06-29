#include "calibrage.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

int main(int argc, char** argv)
{
    std::string inputDir;
    std::string prefixL, prefixR;
    std::string namel, namer; 
    std::string fileExtension;
    bool click;
    bool save;
    std::string cameraType;
    bool useOpenCV;

    //========= Handling Program options =========
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("input,i", boost::program_options::value<std::string>(&inputDir)->default_value("./../data/images"), "Input directory containing chessboard images")
        ("prefix-l", boost::program_options::value<std::string>(&prefixL)->default_value("img_left"), "Prefix of images from left camera")
        ("prefix-r", boost::program_options::value<std::string>(&prefixR)->default_value("img_right"), "Prefix of images from right camera")
        ("name-l", boost::program_options::value<std::string>(&namel)->default_value("camera_1"), "Camera left name")
        ("name-r", boost::program_options::value<std::string>(&namer)->default_value("camera_2"), "Camera right name")
        ("file-extension,e", boost::program_options::value<std::string>(&fileExtension)->default_value(".pgm"), "File extension of images")
        ("click,c", boost::program_options::bool_switch(&click)->default_value(false), "allow mouse click")
        ("save,s", boost::program_options::bool_switch(&save)->default_value(false), "allow calibration table save")
        ("camera-type", boost::program_options::value<std::string>(&cameraType)->default_value("fisheye"), "Camera type: fisheye | pinhole")
        ("opencv", boost::program_options::bool_switch(&useOpenCV)->default_value(false), "Use OpenCV to detect corners")
        ;

    boost::program_options::positional_options_description pdesc;
    pdesc.add("input", 1);

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(pdesc).run(), vm);
    boost::program_options::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    if (!boost::filesystem::exists(inputDir) && !boost::filesystem::is_directory(inputDir))
    {
        std::cerr << "# ERROR: Cannot find input directory " << inputDir << "." << std::endl;
        return 1;
    }

    // look for images in input directory
    std::vector<std::string> imageFilenamesL, imageFilenamesR;
    boost::filesystem::directory_iterator itr;
    for (boost::filesystem::directory_iterator itr(inputDir); itr != boost::filesystem::directory_iterator(); ++itr)
    {
        if (!boost::filesystem::is_regular_file(itr->status()))
        {
            continue;
        }

        std::string filename = itr->path().filename().string();

        // check if file extension matches
        if (filename.compare(filename.length() - fileExtension.length(), fileExtension.length(), fileExtension) != 0)
        {
            continue;
        }

        // check if prefix matches
        if (prefixL.empty() || (!prefixL.empty() && (filename.compare(0, prefixL.length(), prefixL) == 0)))
        {
            imageFilenamesL.push_back(itr->path().string());
        }
        if (prefixR.empty() || (!prefixR.empty() && (filename.compare(0, prefixR.length(), prefixR) == 0)))
        {
            imageFilenamesR.push_back(itr->path().string());
        }
    }

    if (imageFilenamesL.empty() || imageFilenamesR.empty())
    {
        std::cerr << "# ERROR: No chessboard images found." << std::endl;
        return 1;
    }

    if (imageFilenamesL.size() != imageFilenamesR.size())
    {
        std::cerr << "# ERROR: # chessboard images from left and right cameras do not match." << std::endl;
        return 1;
    }

    bool matchImages = true;
    std::sort(imageFilenamesL.begin(), imageFilenamesL.end());
    std::sort(imageFilenamesR.begin(), imageFilenamesR.end());

    for (size_t i = 0; i < imageFilenamesL.size(); ++i)
    {
        std::string filenameL = boost::filesystem::path(imageFilenamesL.at(i)).filename().string();
        std::string filenameR = boost::filesystem::path(imageFilenamesR.at(i)).filename().string();

        if (filenameL.compare(prefixL.length(),
                              filenameL.size() - prefixL.length(),
                              filenameR,
                              prefixR.length(),
                              filenameR.size() - prefixR.length()) != 0)
        {
            matchImages = false;
        }
    }

    if (!matchImages)
    {
        return 1;
    }

   calibrage* stereo = new calibrage(namel, namer, imageFilenamesL, imageFilenamesR, click, save, cameraType, useOpenCV); 

   stereo->modeStereo();  

   delete stereo;

   return 0;
}; 
