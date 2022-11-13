#include "Djb2Test.h"
#include "../../../../../../main/java/net/runelite/cache/util/Djb2.h"

namespace net::runelite::cache::util
{
	using Test = org::junit::Test;
//	import static org.junit.Assert.*;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testHash()
	void Djb2Test::testHash()
	{
		int hash = Djb2::hash(L"l49_52");
		assertEquals(-1153204821, hash);
	}
}
