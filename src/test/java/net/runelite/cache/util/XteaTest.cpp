#include "XteaTest.h"
#include "../../../../../../main/java/net/runelite/cache/util/Xtea.h"

namespace net::runelite::cache::util
{
	using StandardCharsets = java::nio::charset::StandardCharsets;
//	import static org.junit.Assert.assertArrayEquals;
	using Test = org::junit::Test;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test()
	void XteaTest::test()
	{
		std::vector<signed char> data = (std::wstring(L"testtesttest1")).getBytes(StandardCharsets::UTF_8);

		std::vector<int> key = {4, 8, 15, 16};
		std::vector<signed char> encrypted = {121, -18, 48, 64, 120, -42, -113, 77, 116, 101, 115, 116, 49};

		std::shared_ptr<Xtea> xtea = std::make_shared<Xtea>(key);
		std::vector<signed char> encData = xtea->encrypt(data, data.size());
		assertArrayEquals(encrypted, encData);

		xtea = std::make_shared<Xtea>(key);
		std::vector<signed char> decData = xtea->decrypt(encData, encData.size());

		assertArrayEquals(data, decData);
	}
}
