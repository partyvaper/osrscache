#include "XteaKeyManager.h"

namespace net::runelite::cache::util
{
	using Gson = com::google::gson::Gson;
	using TypeToken = com::google::gson::reflect::TypeToken;
	using InputStream = java::io::InputStream;
	using InputStreamReader = java::io::InputStreamReader;
	using StandardCharsets = java::nio::charset::StandardCharsets;
	using HashMap = java::util::HashMap;
	using List = java::util::List;
	using Map = java::util::Map;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> XteaKeyManager::logger = org::slf4j::LoggerFactory::getLogger(XteaKeyManager::class);

	void XteaKeyManager::loadKeys(std::shared_ptr<InputStream> in)
	{
		// CHECKSTYLE:OFF
		std::vector<std::shared_ptr<XteaKey>> k = (std::make_shared<Gson>())->fromJson(std::make_shared<InputStreamReader>(in, StandardCharsets::UTF_8), (std::make_shared<TypeTokenAnonymousInnerClass>(shared_from_this()))->getType());
		// CHECKSTYLE:ON

		for (auto key : k)
		{
			keys.emplace(key->getRegion(), key->getKeys());
		}

		logger->info(L"Loaded {} keys", keys.size());
	}

	XteaKeyManager::TypeTokenAnonymousInnerClass::TypeTokenAnonymousInnerClass(std::shared_ptr<XteaKeyManager> outerInstance) : outerInstance(outerInstance)
	{
	}

	std::vector<int> XteaKeyManager::getKey(int region)
	{
		return keys[region];
	}
}
