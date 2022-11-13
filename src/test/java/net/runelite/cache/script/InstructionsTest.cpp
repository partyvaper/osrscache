#include "InstructionsTest.h"
#include "../../../../../../main/java/net/runelite/cache/script/Instructions.h"

namespace net::runelite::cache::script
{
	using Test = org::junit::Test;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testInit()
	void InstructionsTest::testInit()
	{
		(std::make_shared<Instructions>())->init();
	}
}
