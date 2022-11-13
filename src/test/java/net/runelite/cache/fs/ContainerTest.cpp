#include "ContainerTest.h"
#include "../../../../../../main/java/net/runelite/cache/fs/Container.h"

namespace net::runelite::cache::fs
{
	using IOException = java::io::IOException;
	using Random = java::util::Random;
//	import static net.runelite.cache.fs.jagex.CompressionType.GZ;
//	import static org.junit.Assert.assertArrayEquals;
	using Test = org::junit::Test;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testCompress() throws java.io.IOException
	void ContainerTest::testCompress()
	{
		std::vector<int> keys = {4, 8, 15, 16};
		std::shared_ptr<Random> random = std::make_shared<Random>(42LL);
		std::vector<signed char> data(1024);
		random->nextBytes(data);

		std::shared_ptr<Container> container = std::make_shared<Container>(GZ, -1);
		container->compress(data, keys);
		std::vector<signed char> compressedData = container->data;

		container = Container::decompress(compressedData, keys);
		assertArrayEquals(data, container->data);
	}
}
