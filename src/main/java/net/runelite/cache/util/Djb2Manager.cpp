#include "Djb2Manager.h"

namespace net::runelite::cache::util
{
	using IOException = java::io::IOException;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using Properties = java::util::Properties;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> Djb2Manager::logger = org::slf4j::LoggerFactory::getLogger(Djb2Manager::class);

	void Djb2Manager::load()
	{
		std::shared_ptr<Properties> properties = std::make_shared<Properties>();
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		properties->load(Djb2Manager::class->getResourceAsStream(L"/djb2.properties"));

		for (auto key : properties)
		{
			int hash = std::stoi(static_cast<std::wstring>(key.first));
			std::wstring value = properties->getProperty(static_cast<std::wstring>(key.first));

			hashes.emplace(hash, value);
		}

		logger->info(L"Loaded {} djb2 hashes", hashes.size());
	}

	std::wstring Djb2Manager::getName(int hash)
	{
		return hashes[hash];
	}
}
