#include "DataFileTest.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/jagex/DataFile.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/jagex/CompressionType.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/jagex/DataFileWriteResult.h"

namespace net::runelite::cache::fs::jagex
{
	using File = java::io::File;
	using IOException = java::io::IOException;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using Container = net::runelite::cache::fs::Container;
	using Assert = org::junit::Assert;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test1() throws java.io.IOException
	void DataFileTest::test1()
	{
		std::shared_ptr<File> file = folder->newFile();
		std::shared_ptr<DataFile> df = std::make_shared<DataFile>(file);

		std::shared_ptr<Container> container = std::make_shared<Container>(CompressionType::NONE, 0);
		container->compress((std::wstring(L"test")).getBytes(), std::vector<int>());
		std::vector<signed char> compressedData = container->data;
		std::shared_ptr<DataFileWriteResult> res = df->write(42, 3, compressedData);

		compressedData = df->read(42, 3, res->sector, res->compressedLength);
		std::shared_ptr<Container> res2 = Container::decompress(compressedData, std::vector<int>());

		std::vector<signed char> buf = res2->data;
		std::wstring str = std::wstring(buf);
		Assert::assertEquals(L"test", str);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test2() throws java.io.IOException
	void DataFileTest::test2()
	{
		std::vector<signed char> b(1024);
		for (int i = 0; i < 1024; ++i)
		{
			b[i] = static_cast<signed char>(i);
		}

		std::shared_ptr<File> file = folder->newFile();

		std::shared_ptr<DataFile> df = std::make_shared<DataFile>(file);

		std::shared_ptr<Container> container = std::make_shared<Container>(CompressionType::BZ2, 42);
		container->compress(b, std::vector<int>());
		std::vector<signed char> compressedData = container->data;
		std::shared_ptr<DataFileWriteResult> res = df->write(42, 0x1FFFF, compressedData);

		compressedData = df->read(42, 0x1FFFF, res->sector, res->compressedLength);
		std::shared_ptr<Container> res2 = Container::decompress(compressedData, std::vector<int>());

		std::vector<signed char> buf = res2->data;
		Assert::assertArrayEquals(b, buf);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testGZipCompression() throws java.io.IOException
	void DataFileTest::testGZipCompression()
	{
		std::shared_ptr<DataFile> df = std::make_shared<DataFile>(folder->newFile());

		std::shared_ptr<Container> container = std::make_shared<Container>(CompressionType::GZ, 0);
		container->compress((std::wstring(L"test")).getBytes(), std::vector<int>());
		std::vector<signed char> compressedData = container->data;
		std::shared_ptr<DataFileWriteResult> res = df->write(41, 4, compressedData);

		compressedData = df->read(41, 4, res->sector, res->compressedLength);
		std::shared_ptr<Container> res2 = Container::decompress(compressedData, std::vector<int>());

		std::vector<signed char> buf = res2->data;
		std::wstring str = std::wstring(buf);
		Assert::assertEquals(L"test", str);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testBZip2Compression() throws java.io.IOException
	void DataFileTest::testBZip2Compression()
	{
		std::shared_ptr<DataFile> df = std::make_shared<DataFile>(folder->newFile());

		std::shared_ptr<Container> container = std::make_shared<Container>(CompressionType::BZ2, 5);
		container->compress((std::wstring(L"test")).getBytes(), std::vector<int>());
		std::vector<signed char> compressedData = container->data;
		std::shared_ptr<DataFileWriteResult> res = df->write(41, 4, compressedData);

		compressedData = df->read(41, 4, res->sector, res->compressedLength);
		std::shared_ptr<Container> res2 = Container::decompress(compressedData, std::vector<int>());

		std::vector<signed char> buf = res2->data;
		std::wstring str = std::wstring(buf);
		Assert::assertEquals(L"test", str);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testEnc() throws java.io.IOException
	void DataFileTest::testEnc()
	{
		std::shared_ptr<File> file = folder->newFile();
		std::vector<int> keys = {4, 8, 15, 16};

		std::shared_ptr<DataFile> df = std::make_shared<DataFile>(file);

		std::shared_ptr<Container> container = std::make_shared<Container>(CompressionType::NONE, 42);
		container->compress((std::wstring(L"testtesttesttest1")).getBytes(), keys);
		std::vector<signed char> compressedData = container->data;
		std::shared_ptr<DataFileWriteResult> res = df->write(42, 3, compressedData);

		compressedData = df->read(42, 3, res->sector, res->compressedLength);
		std::shared_ptr<Container> res2 = Container::decompress(compressedData, keys);

		std::vector<signed char> buf = res2->data;
		std::wstring str = std::wstring(buf);
		Assert::assertEquals(L"testtesttesttest1", str);
		Assert::assertEquals(42, res2->revision);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testEncGz() throws java.io.IOException
	void DataFileTest::testEncGz()
	{
		std::shared_ptr<File> file = folder->newFile();
		std::vector<int> keys = {4, 8, 15, 16};

		std::shared_ptr<DataFile> df = std::make_shared<DataFile>(file);

		std::shared_ptr<Container> container = std::make_shared<Container>(CompressionType::GZ, 42);
		container->compress((std::wstring(L"testtesttesttest1")).getBytes(), keys);
		std::vector<signed char> compressedData = container->data;
		std::shared_ptr<DataFileWriteResult> res = df->write(42, 3, compressedData);

		compressedData = df->read(42, 3, res->sector, res->compressedLength);
		std::shared_ptr<Container> res2 = Container::decompress(compressedData, keys);

		std::vector<signed char> buf = res2->data;
		std::wstring str = std::wstring(buf);
		Assert::assertEquals(L"testtesttesttest1", str);
		Assert::assertEquals(42, res2->revision);
	}
}
