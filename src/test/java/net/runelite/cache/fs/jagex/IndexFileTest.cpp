#include "IndexFileTest.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/jagex/IndexFile.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/jagex/IndexEntry.h"

namespace net::runelite::cache::fs::jagex
{
	using File = java::io::File;
	using IOException = java::io::IOException;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using Assert = org::junit::Assert;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test() throws java.io.IOException
	void IndexFileTest::test()
	{
		std::shared_ptr<File> file = folder->newFile();
		std::shared_ptr<IndexFile> index = std::make_shared<IndexFile>(5, file);
		std::shared_ptr<IndexEntry> entry = std::make_shared<IndexEntry>(index, 7, 8, 9);
		index->write(entry);
		std::shared_ptr<IndexEntry> entry2 = index->read(7);
		Assert::assertEquals(entry, entry2);
	}
}
