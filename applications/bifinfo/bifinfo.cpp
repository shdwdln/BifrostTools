#include <bifrostapi/bifrost_om.h>
#include <bifrostapi/bifrost_stateserver.h>
#include <bifrostapi/bifrost_component.h>
#include <bifrostapi/bifrost_fileio.h>
#include <bifrostapi/bifrost_fileutils.h>
#include <bifrostapi/bifrost_string.h>
#include <bifrostapi/bifrost_stringarray.h>
#include <bifrostapi/bifrost_refarray.h>
#include <bifrostapi/bifrost_channel.h>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <stdexcept>

namespace po = boost::program_options;

// A helper function to simplify the main part.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, " "));
    return os;
}

enum BBOX { None, PointsOnly, PointsWithVelocity };

inline std::ostream& operator<<(std::ostream & os, BBOX & bbox)
{
    switch (bbox) {
     case None:
         os << "None";
         break;
     case PointsOnly:
         os << "Points only";
         break;
     case PointsWithVelocity:
         os << "Points with velocity";
     }
     return os;
}

inline std::istream & operator>>(std::istream & str, BBOX & bbox) {
  unsigned int bbox_type = 0;
  if (str >> bbox_type)
    bbox = static_cast<BBOX>(bbox_type);
  return str;
}

void process_bifrost_file(const std::string& bifrost_filename,
                          const std::string& position_channel_name,
                          const std::string& velocity_channel_name,
                          BBOX bbox_type,
                          const float* fps=0)
{
    Bifrost::API::String biffile = bifrost_filename.c_str();
    Bifrost::API::ObjectModel om;
    Bifrost::API::FileIO fileio = om.createFileIO( biffile );
    const Bifrost::API::BIF::FileInfo& info = fileio.info();

    std::cout << boost::format("Version        : %1%") % info.version << std::endl;
    std::cout << boost::format("Frame          : %1%") % info.frame << std::endl;
    std::cout << boost::format("Channel count  : %1%") % info.channelCount << std::endl;
    std::cout << boost::format("Component name : %1%") % info.componentName.c_str() << std::endl;
    std::cout << boost::format("Component type : %1%") % info.componentType << std::endl;
    std::cout << boost::format("Object name    : %1%") % info.objectName.c_str() << std::endl;
    std::cout << boost::format("Layout name    : %1%") % info.layoutName.c_str() << std::endl;

    for (size_t channelIndex=0;channelIndex<info.channelCount;channelIndex++)
    {
        std::cout << std::endl;
        const Bifrost::API::BIF::FileInfo::ChannelInfo& channelInfo = fileio.channelInfo(channelIndex);
        std::cout << boost::format("        Channel name  : %1%") % channelInfo.name.c_str() << std::endl;
        std::cout << boost::format("        Data type     : %1%") % channelInfo.dataType << std::endl;
        std::cout << boost::format("        Max depth     : %1%") % channelInfo.maxDepth << std::endl;
        std::cout << boost::format("        Tile count    : %1%") % channelInfo.tileCount << std::endl;
        std::cout << boost::format("        Element count : %1%") % channelInfo.elementCount << std::endl;
    }

    if (bbox_type != BBOX::None)
    {
        // Need to load the entire file's content to process
        Bifrost::API::StateServer ss = fileio.load( );
        if (ss.valid())
        {

        }
        else
        {
            std::cerr << boost::format("Unable to load the content of the Bifrost file \"%1%\"") % bifrost_filename.c_str()
                      << std::endl;
            return;
        }
    }
}

int main(int argc, char **argv)
{

    try {
        typedef std::vector<std::string> StringContainer;
        std::string position_channel_name("position");
        std::string velocity_channel_name("velocity");
        BBOX bbox_type = BBOX::None;
        std::string bifrost_filename;
        float fps = 24.0f;
        po::options_description desc("Allowed options");
        desc.add_options()
            ("version", "print version string")
            ("help", "produce help message")
            ("bbox", po::value<BBOX>(&bbox_type), "Analyze the entire file to obtain the overall bounding box [0:None, 1:PointsOnly, 2:PointsWithVelocity]")
            ("fps", po::value<float>(&fps),
                    "Frames per second to scale velocity when determining the velocity-attenuated bounding box. Defaults to 24.0")
            ("input-file", po::value<std::vector<std::string> >(),
             "input files")
            ;

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 1;
        }
        if (vm.count("input-file"))
        {
            std::cout << "Input files are: "
                      << vm["input-file"].as< std::vector<std::string> >() << "\n";
            if (vm["input-file"].as< std::vector<std::string> >().size() == 1)
            {
                bifrost_filename = vm["input-file"].as< std::vector<std::string> >()[0];
            }
            else
            {
                std::cout << desc << "\n";
                return 1;
            }
        }
        std::cout << "fps = " << fps << std::endl;
        if (bifrost_filename.size()>0)
            process_bifrost_file(bifrost_filename,
                                 position_channel_name,
                                 velocity_channel_name,
                                 bbox_type,
                                 bbox_type==BBOX::PointsWithVelocity?&fps:0);
        else
        {
            std::cout << desc << "\n";
            return 1;
        }
    }
    catch(std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;

}
