#include "NpcExporter.h"

namespace net::runelite::cache::definitions::exporters
{
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using FileWriter = java::io::FileWriter;
	using IOException = java::io::IOException;
	using NpcDefinition = net::runelite::cache::definitions::NpcDefinition;

	NpcExporter::NpcExporter(std::shared_ptr<NpcDefinition> npc) : npc(npc), gson(builder::create())
	{

		std::shared_ptr<GsonBuilder> builder = (std::make_shared<GsonBuilder>())->setPrettyPrinting();
	}

	std::wstring NpcExporter::export_Keyword()
	{
		return gson->toJson(npc);
	}

	void NpcExporter::exportTo(std::shared_ptr<File> file)
	{
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.FileWriter fw = new java.io.FileWriter(file))
		{
			FileWriter fw = FileWriter(file);
			fw.write(export_Keyword());
		}
	}
}
