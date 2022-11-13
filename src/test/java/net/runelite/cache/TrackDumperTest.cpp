#include "TrackDumperTest.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using File = java::io::File;
	using FileInputStream = java::io::FileInputStream;
	using IOException = java::io::IOException;
	using MidiSystem = javax::sound::midi::MidiSystem;
	using Sequencer = javax::sound::midi::Sequencer;
	using TrackDefinition = net::runelite::cache::definitions::TrackDefinition;
	using TrackLoader = net::runelite::cache::definitions::loaders::TrackLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using Djb2Manager = net::runelite::cache::util::Djb2Manager;
	using Ignore = org::junit::Ignore;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> TrackDumperTest::logger = org::slf4j::LoggerFactory::getLogger(TrackDumperTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test() throws java.io.IOException
	void TrackDumperTest::test()
	{
		std::shared_ptr<File> dumpDir1 = folder->newFolder(), dumpDir2 = folder->newFolder();
		int idx1 = 0, idx2 = 0;

		djb2->load();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::MUSIC_TRACKS);
			std::shared_ptr<Index> index2 = store.getIndex(IndexType::MUSIC_JINGLES);

			for (auto archive : index->getArchives())
			{
				dumpTrackArchive(dumpDir1, storage, archive);
				++idx1;
			}

			for (auto archive : index2->getArchives())
			{
				dumpTrackArchive(dumpDir2, storage, archive);
				++idx2;
			}
		}

		logger->info(L"Dumped {} sound tracks ({} idx1, {} idx2) to {} and {}", idx1 + idx2, idx1, idx2, dumpDir1, dumpDir2);
	}

	void TrackDumperTest::dumpTrackArchive(std::shared_ptr<File> dumpDir, std::shared_ptr<Storage> storage, std::shared_ptr<Archive> archive)
	{
		std::vector<signed char> contents = archive->decompress(storage->loadArchive(archive));

		if (contents.empty())
		{
			return;
		}

		std::shared_ptr<TrackLoader> loader = std::make_shared<TrackLoader>();
		std::shared_ptr<TrackDefinition> def = loader->load(contents);

		std::wstring name;
		if (archive->getNameHash() != 0)
		{
			name = djb2->getName(archive->getNameHash());
			if (name == L"")
			{
				name = L"name-" + std::to_wstring(archive->getNameHash());
			}
		}
		else
		{
			name = L"archive-" + std::to_wstring(archive->getArchiveId());
		}

		std::shared_ptr<File> dest = std::make_shared<File>(dumpDir, name + L".midi");
		assert(!dest->exists());

		Files::write(def->midi, dest);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void play() throws Exception
	void TrackDumperTest::play()
	{
		// Obtains the default Sequencer connected to a default device.
		std::shared_ptr<Sequencer> sequencer = MidiSystem::getSequencer();

		// Opens the device, indicating that it should now acquire any
		// system resources it requires and become operational.
		sequencer->open();

		try
		{
			// create a stream from a file
			std::shared_ptr<java::io::InputStream> is = std::make_shared<FileInputStream>(std::make_shared<File>(L"D:\\rs\\07\\cache\\track1\\name-687938017.midi"));

			// Sets the current sequence on which the sequencer operates.
			// The stream must point to MIDI file data.
			sequencer->setSequence(is);

			// Starts playback of the MIDI data in the currently loaded sequence.
			sequencer->start();

			while (sequencer->isRunning())
			{
				delay(1000LL);
			}
		}
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the exception 'finally' clause:
		finally
		{
			sequencer->close();
		}
	}
}
