#include "StoreLocation.h"
#include "CacheProperties.h"

namespace net::runelite::cache
{
	using Strings = com::google::common::base::Strings;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using InputStream = java::io::InputStream;
	using Files = java::nio::file::Files;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> StoreLocation::logger = org::slf4j::LoggerFactory::getLogger(StoreLocation::class);
std::shared_ptr<java::io::File> StoreLocation::LOCATION;
std::shared_ptr<java::io::File> StoreLocation::TMP;

	StoreLocation::StaticConstructor::StaticConstructor()
	{
	std::wstring cacheTmpDir = System::getProperty(L"cache.tmpdir");
	if (!Strings::isNullOrEmpty(cacheTmpDir))
	{
		System::setProperty(L"java.io.tmpdir", cacheTmpDir);
		TMP = std::make_shared<File>(cacheTmpDir);
	}
            
	try
	{
		LOCATION = setupCacheDir();
	}
	catch (const IOException &ex)
	{
		logger->warn(L"unable to initialize cache tmp area", ex);
	}
	}

StoreLocation::StaticConstructor StoreLocation::staticConstructor;

	std::shared_ptr<File> StoreLocation::setupCacheDir()
	{
		std::shared_ptr<File> file = std::make_shared<File>(System::getProperty(L"java.io.tmpdir"), L"cache-" + std::to_wstring(CacheProperties::getCacheVersion()));

		if (file->exists())
		{
			logger->info(L"Using preexisting cache working directory {}", file);
			return file;
		}

		file->mkdir();

		// Copy over files
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		std::shared_ptr<InputStream> in = StoreLocation::class->getResourceAsStream(L"/main_file_cache.dat2");
		Files::copy(in, (std::make_shared<File>(file, L"main_file_cache.dat2"))->toPath());

//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		in = StoreLocation::class->getResourceAsStream(L"/main_file_cache.idx255");
		Files::copy(in, (std::make_shared<File>(file, L"main_file_cache.idx255"))->toPath());

		for (int i = 0; i <= NUM_INDEXES; ++i)
		{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
			in = StoreLocation::class->getResourceAsStream(L"/main_file_cache.idx" + std::to_wstring(i));
			Files::copy(in, (std::make_shared<File>(file, L"main_file_cache.idx" + std::to_wstring(i)))->toPath());
		}

		logger->info(L"Set up cache working directory to {}", file);

		return file;
	}

	std::shared_ptr<TemporaryFolder> StoreLocation::getTemporaryFolder()
	{
		return std::make_shared<TemporaryFolderAnonymousInnerClass>();
	}

	void StoreLocation::TemporaryFolderAnonymousInnerClass::after()
	{
		// don't cleanup if using cache tmpdir
		if (TMP == nullptr)
		{
			org::junit::rules::TemporaryFolder::after();
		}
	}
}
