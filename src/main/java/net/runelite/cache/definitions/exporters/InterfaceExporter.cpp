#include "InterfaceExporter.h"

namespace net::runelite::cache::definitions::exporters
{
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using FileWriter = java::io::FileWriter;
	using IOException = java::io::IOException;
	using InterfaceDefinition = net::runelite::cache::definitions::InterfaceDefinition;

	InterfaceExporter::InterfaceExporter(std::shared_ptr<InterfaceDefinition> item) : item(item), gson(builder::create())
	{

		std::shared_ptr<GsonBuilder> builder = (std::make_shared<GsonBuilder>())->setPrettyPrinting();
	}

	std::wstring InterfaceExporter::export_Keyword()
	{
		return gson->toJson(item);
	}

	void InterfaceExporter::exportTo(std::shared_ptr<File> file)
	{
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.FileWriter fw = new java.io.FileWriter(file))
		{
			FileWriter fw = FileWriter(file);
			fw.write(export_Keyword());
		}
	}
}
