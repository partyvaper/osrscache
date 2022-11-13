#include "DisassemblerTest.h"
#include "../../../../../../../main/java/net/runelite/cache/script/disassembler/Disassembler.h"

namespace net::runelite::cache::script::disassembler
{
	using Files = com::google::common::io::Files;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using StandardCharsets = java::nio::charset::StandardCharsets;
	using IndexType = net::runelite::cache::IndexType;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using ScriptLoader = net::runelite::cache::definitions::loaders::ScriptLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> DisassemblerTest::logger = org::slf4j::LoggerFactory::getLogger(DisassemblerTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test() throws java.io.IOException
	void DisassemblerTest::test()
	{
		std::shared_ptr<File> outDir = folder->newFolder();
		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(net.runelite.cache.StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::CLIENTSCRIPT);
			std::shared_ptr<ScriptLoader> loader = std::make_shared<ScriptLoader>();

			for (auto archive : index->getArchives())
			{
				std::vector<signed char> contents = archive->decompress(storage->loadArchive(archive));

				if (contents.empty())
				{
					continue;
				}

				std::shared_ptr<ScriptDefinition> script = loader->load(archive->getArchiveId(), contents);

				std::shared_ptr<File> outFile = std::make_shared<File>(outDir, std::to_wstring(archive->getArchiveId()) + L".rs2asm");

				std::shared_ptr<Disassembler> disassembler = std::make_shared<Disassembler>();
				std::wstring out = disassembler->disassemble(script);

				Files::write(out.getBytes(StandardCharsets::UTF_8), outFile);

				++count;
			}
		}

		logger->info(L"Dumped {} scripts to {}", count, outDir);
	}
}
