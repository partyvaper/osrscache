#include "OutputStreamTest.h"
#include "../../../../../../main/java/net/runelite/cache/io/OutputStream.h"
#include "../../../../../../main/java/net/runelite/cache/io/InputStream.h"

namespace net::runelite::cache::io
{
//	import static org.junit.Assert.assertEquals;
	using Test = org::junit::Test;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testWriteBigSmart()
	void OutputStreamTest::testWriteBigSmart()
	{
		std::shared_ptr<OutputStream> os = std::make_shared<OutputStream>();
		os->writeBigSmart(42);
		os->writeBigSmart(70000);
		os->writeBigSmart(65535);

		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(os->getArray());
		assertEquals(42, is->readBigSmart());
		assertEquals(70000, is->readBigSmart());
		assertEquals(65535, is->readBigSmart());
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testWriteString()
	void OutputStreamTest::testWriteString()
	{
		std::vector<wchar_t> c = {32, 160};
		std::wstring str = std::wstring(c, 0, c.size());

		std::shared_ptr<OutputStream> os = std::make_shared<OutputStream>();
		os->writeString(str);

		// 1 byte length + 32 + 160
		assertEquals(3, os->getOffset());
	}
}
