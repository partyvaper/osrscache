#include "CacheProperties.h"
#include "StoreLocation.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using InputStream = java::io::InputStream;
	using Properties = java::util::Properties;

	std::shared_ptr<Properties> CacheProperties::getProperties()
	{
		std::shared_ptr<Properties> properties = std::make_shared<Properties>();
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		std::shared_ptr<InputStream> resourceAsStream = StoreLocation::class->getResourceAsStream(L"/cache.properties");
		properties->load(resourceAsStream);
		return properties;
	}

	int CacheProperties::getRsVersion()
	{
		return static_cast<int>(static_cast<Double>(getProperties()->getProperty(L"rs.version")));
	}

	int CacheProperties::getCacheVersion()
	{
		return static_cast<int>(getProperties()->getProperty(L"cache.version"));
	}
}
