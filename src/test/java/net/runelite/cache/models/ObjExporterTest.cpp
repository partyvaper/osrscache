#include "ObjExporterTest.h"
#include "../../../../../../main/java/net/runelite/cache/models/ObjExporter.h"

namespace net::runelite::cache::models
{
	using File = java::io::File;
	using FileWriter = java::io::FileWriter;
	using PrintWriter = java::io::PrintWriter;
	using Files = java::nio::file::Files;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using TextureManager = net::runelite::cache::TextureManager;
	using ModelDefinition = net::runelite::cache::definitions::ModelDefinition;
	using ModelLoader = net::runelite::cache::definitions::loaders::ModelLoader;
	using Store = net::runelite::cache::fs::Store;
	using Ignore = org::junit::Ignore;
	using Test = org::junit::Test;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void testExport() throws Exception
	void ObjExporterTest::testExport()
	{
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(net.runelite.cache.StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<TextureManager> tm = std::make_shared<TextureManager>(store);
			tm->load();

			std::shared_ptr<ModelLoader> loader = std::make_shared<ModelLoader>();
			std::shared_ptr<ModelDefinition> model = loader->load(9638, Files::readAllBytes((std::make_shared<File>(L"D:\\rs\\07\\cache\\models\\9638.model"))->toPath()));

			std::shared_ptr<ObjExporter> exporter = std::make_shared<ObjExporter>(tm, model);
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.PrintWriter objWriter = new java.io.PrintWriter(new java.io.FileWriter(new java.io.File("D:\\rs\\07\\temp\\9638.obj"))); java.io.PrintWriter mtlWriter = new java.io.PrintWriter(new java.io.FileWriter(new java.io.File("D:\\rs\\07\\temp\\9638.mtl"))))
			{
				PrintWriter objWriter = PrintWriter(std::make_shared<FileWriter>(std::make_shared<File>(L"D:\\rs\\07\\temp\\9638.obj")));
				PrintWriter mtlWriter = PrintWriter(std::make_shared<FileWriter>(std::make_shared<File>(L"D:\\rs\\07\\temp\\9638.mtl")));
				exporter->export_Keyword(objWriter, mtlWriter);
			}
		}
	}
}
