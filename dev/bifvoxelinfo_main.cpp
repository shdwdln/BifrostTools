#include <utils/BifrostUtils.h>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <OpenEXR/ImathBox.h>

#include <BifrostHeaders.h>

typedef std::vector<Bifrost::API::String> StringContainer;

namespace po = boost::program_options;

// A helper function to simplify the main part.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, " "));
	return os;
}

void process_VoxelComponentType(const Bifrost::API::Component& component)
{
	{
		std::cout << "process_VoxelComponentType() START" << std::endl;
		Bifrost::API::Layout layout = component.layout();
		size_t depth_count = layout.depthCount();
		Bifrost::API::RefArray channel_array = component.channels();
		size_t num_channels = channel_array.count();
		std::cout << boost::format("process_VoxelComponentType() number of channels %1%") % num_channels << std::endl;
		for (size_t channel_index = 0; channel_index < num_channels; ++channel_index)
		{
			const Bifrost::API::Channel current_channel = channel_array[channel_index];
			size_t channel_element_count = current_channel.elementCount();
			std::cout << boost::format("process_VoxelComponentType() channel_element_count %1%") % channel_element_count << std::endl;
			for (size_t depth_index = 0; depth_index < depth_count; depth_index++) {
				Bifrost::API::TileDimInfo tile_dim_info = layout.tileDimInfo(depth_index);
				std::cout << boost::format("process_VoxelComponentType() tile_dim_info[%1%][%2%] tileSize = %3%, tileWidth = %4%, depthWidth = %5%, voxelWidth = %6%")
					% current_channel.name()
					% depth_index
					% tile_dim_info.tileSize
					% tile_dim_info.tileWidth
					% tile_dim_info.depthWidth
					% tile_dim_info.voxelWidth
					<< std::endl;
				size_t tile_count = layout.tileCount(depth_index);
				for (size_t tile_index = 0; tile_index < tile_count; tile_index++) {
					Bifrost::API::TreeIndex tree_index(tile_index, depth_index);
					switch (current_channel.dataType())
					{
					case Bifrost::API::FloatType: //,		/*!< Type float */
												  // std::cout << "Channel type is FloatType" << std::endl;
					{

						const Bifrost::API::TileData<float>& channel_data = current_channel.tileData<float>(tree_index);
						size_t channel_data_count = channel_data.count();
						std::cout << boost::format("process_VoxelComponentType() channel[%1%] count = %2%") % current_channel.name() % channel_data_count << std::endl;
						for (size_t channel_data_index = 0; channel_data_index<channel_data_count; channel_data_index++) {
							// std::cout << boost::format("process_VoxelComponentType() channel[%1%][%2%] =  %3%") % current_channel.name() % channel_data_index % channel_data[channel_data_index] << std::endl;
						}
					}
					break;
					case Bifrost::API::FloatV2Type: //,	/*!< Type amino::Math::vec2f */
													// std::cout << "Channel type is FloatV2Type" << std::endl;
						break;
					case Bifrost::API::FloatV3Type: //,	/*!< Type amino::Math::vec3f */
						std::cout << "Channel type is FloatV3Type" << std::endl;
						break;
					case Bifrost::API::Int32Type: //,		/*!< Type int32_t */
						std::cout << "Channel type is Int32Type" << std::endl;
						break;
					case Bifrost::API::Int64Type: //,		/*!< Type int64_t */
						std::cout << "Channel type is Int64Type" << std::endl;
						break;
					case Bifrost::API::UInt32Type: //,		/*!< Type uint32_t */
						std::cout << "Channel type is UInt32Type" << std::endl;
						break;
					case Bifrost::API::UInt64Type: //,		/*!< Type uint64_t */
						std::cout << "Channel type is UInt64Type" << std::endl;
						break;
					case Bifrost::API::Int32V2Type: //,	/*!< Type amino::Math::vec2i */
						std::cout << "Channel type is Int32V2Type" << std::endl;
						break;
					case Bifrost::API::Int32V3Type: //,	/*!< Type amino::Math::vec3i */
						std::cout << "Channel type is Int32V3Type" << std::endl;
						break;
					case Bifrost::API::FloatV4Type: //,	/*!< Type amino::Math::vec4f */
						std::cout << "Channel type is FloatV4Type" << std::endl;
						break;
					case Bifrost::API::FloatMat44Type: //,	/*!< Type amino::Math::mat44f */
						std::cout << "Channel type is FloatMat44Type" << std::endl;
						break;
					case Bifrost::API::Int8Type: //,		/*!< Type int8_t */
						std::cout << "Channel type is Int8Type" << std::endl;
						break;
					case Bifrost::API::Int16Type: //,		/*!< Type int16_t */
						std::cout << "Channel type is Int16Type" << std::endl;
						break;
					case Bifrost::API::UInt8Type: //,		/*!< Type uint8_t */
						std::cout << "Channel type is UInt8Type" << std::endl;
						break;
					case Bifrost::API::UInt16Type: //,		/*!< Type uint16_t */
						std::cout << "Channel type is UInt16Type" << std::endl;
						break;
					case Bifrost::API::BoolType: //,		/*!< Type bool */
						std::cout << "Channel type is BoolType" << std::endl;
						break;
					case Bifrost::API::StringClassType: //,	/*!< Type Bifrost::API::String class */
						std::cout << "Channel type is StringClassType" << std::endl;
						break;
					case Bifrost::API::DictionaryClassType: //,	/*!< Type Bifrost::API::Dictionary class */
						std::cout << "Channel type is DictionaryClassType" << std::endl;
						break;
					case Bifrost::API::UInt64V2Type: //,	/*!< Type amino::Math::vec2ui64 */
						std::cout << "Channel type is UInt64V2Type" << std::endl;
						break;
					case Bifrost::API::UInt64V3Type: //,	/*!< Type amino::Math::vec3ui64 */
						std::cout << "Channel type is UInt64V3Type" << std::endl;
						break;
					case Bifrost::API::UInt64V4Type: //,	/*!< Type amino::Math::vec4ui64 */
						std::cout << "Channel type is UInt64V4Type" << std::endl;
						break;
					case Bifrost::API::StringArrayClassType: // /*!< Type Bifrost::API::StringArray class */
						std::cout << "Channel type is StringArrayClassType" << std::endl;
						break;
					case Bifrost::API::NoneType: // = 0,		/*!< Undefined data type */
						std::cout << "Channel type is NoneType" << std::endl;
						break;
					}
				}
			}
		}
	}

	std::cout << "process_VoxelComponentType() END" << std::endl;
}

int process_bifrost_voxel(const std::string& bifrost_filename)
{
	// using namespace Bifrost::API;

	Bifrost::API::String biffile = bifrost_filename.c_str();
	Bifrost::API::ObjectModel om;
	Bifrost::API::FileIO fileio = om.createFileIO(biffile);
	Bifrost::API::StateServer ss = fileio.load();
	if (ss.valid())
	{
		const Bifrost::API::BIF::FileInfo& info = fileio.info();

		std::cout << boost::format("Version        : %1%") % info.version << std::endl;
		std::cout << boost::format("Frame          : %1%") % info.frame << std::endl;
		std::cout << boost::format("Channel count  : %1%") % info.channelCount << std::endl;
		std::cout << boost::format("Component name : %1%") % info.componentName.c_str() << std::endl;
		std::cout << boost::format("Component type : %1%") % info.componentType.c_str() << std::endl;
		std::cout << boost::format("Object name    : %1%") % info.objectName.c_str() << std::endl;
		std::cout << boost::format("Layout name    : %1%") % info.layoutName.c_str() << std::endl;

		StringContainer channel_names;
		for (size_t channelIndex = 0; channelIndex<info.channelCount; channelIndex++)
		{
			std::cout << std::endl;
			const Bifrost::API::BIF::FileInfo::ChannelInfo& channelInfo = fileio.channelInfo(channelIndex);
			std::cout << boost::format("\t""Channel name  : %1%") % channelInfo.name.c_str() << std::endl;
			std::cout << boost::format("\t""Data type     : %1%") % channelInfo.dataType << std::endl;
			std::cout << boost::format("\t""Max depth     : %1%") % channelInfo.maxDepth << std::endl;
			std::cout << boost::format("\t""Tile count    : %1%") % channelInfo.tileCount << std::endl;
			std::cout << boost::format("\t""Element count : %1%") % channelInfo.elementCount << std::endl;
			channel_names.push_back(channelInfo.name);
		}

		size_t numComponents = ss.components().count();
		std::cout << boost::format("StateServer components count : %1%") % numComponents << std::endl;
		for (size_t componentIndex = 0; componentIndex<numComponents; componentIndex++)
		{
			Bifrost::API::Component component = ss.components()[componentIndex];
			Bifrost::API::TypeID componentType = component.type();
			std::cout << boost::format("component[%1%] of type %2%") % componentIndex % componentType << std::endl;
			if (componentType == Bifrost::API::VoxelComponentType)
			{
				process_VoxelComponentType(component);
			}
		}


	}

	return 0;
}

int main(int argc, char **argv)
{

	try {
		typedef std::vector<std::string> StringContainer;
		std::string bifrost_filename;
		po::options_description desc("Allowed options");
		desc.add_options()
			("version", "print version string")
			("help", "produce help message")
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
		if (bifrost_filename.size() > 0)
		{
			// process_bifrost_voxel(bifrost_filename);
		}
		else
		{
			std::cout << desc << "\n";
			return 1;
		}
	}
	catch (std::exception& e) {
		std::cerr << "error: " << e.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cerr << "Exception of unknown type!\n";
	}

	return 0;

}
