#include "calibrage.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

int main(int argc, char** argv)
{
    std::string inputDir;
    std::string prefix;
    std::string name;
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
        ("prefix,p", boost::program_options::value<std::string>(&prefix)->default_value("image"), "Prefix of images")
        ("name,n", boost::program_options::value<std::string>(&name)->default_value("camera_0"), "Camera name")
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
    std::vector<std::string> imageFilenames;
    boost::filesystem::directory_iterator itr;
    for (boost::filesystem::directory_iterator itr(inputDir); itr != boost::filesystem::directory_iterator(); ++itr)
    {
        if (!boost::filesystem::is_regular_file(itr->status()))
        {
            continue;
        }

        std::string filename = itr->path().filename().string();

        // check if prefix matches
        if (!prefix.empty())
        {
            if (filename.compare(0, prefix.length(), prefix) != 0)
            {
                continue;
            }
        }

        // check if file extension matches
        if (filename.compare(filename.length() - fileExtension.length(), fileExtension.length(), fileExtension) != 0)
        {
            continue;
        }

        imageFilenames.push_back(itr->path().string());
    }

    if (imageFilenames.empty())
    {
        std::cerr << "# ERROR: No chessboard images found." << std::endl;
        return 1;
    }

   calibrage* mono = new calibrage(name, imageFilenames, click, save, cameraType, useOpenCV); 

   mono->modeMono();  

   delete mono;

   return 0;
}; 
