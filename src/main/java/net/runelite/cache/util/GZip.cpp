#include "GZip.h"

namespace net::runelite::cache::util
{
	using ByteArrayInputStream = java::io::ByteArrayInputStream;
	using ByteArrayOutputStream = java::io::ByteArrayOutputStream;
	using IOException = java::io::IOException;
	using InputStream = java::io::InputStream;
	using OutputStream = java::io::OutputStream;
	using GZIPInputStream = java::util::zip::GZIPInputStream;
	using GZIPOutputStream = java::util::zip::GZIPOutputStream;
	using IOUtils = org::apache::commons::compress::utils::IOUtils;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> GZip::logger = org::slf4j::LoggerFactory::getLogger(GZip::class);

	std::vector<signed char> GZip::compress(std::vector<signed char> &bytes)
	{
		std::shared_ptr<InputStream> is = std::make_shared<ByteArrayInputStream>(bytes);
		std::shared_ptr<ByteArrayOutputStream> bout = std::make_shared<ByteArrayOutputStream>();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.OutputStream os = new java.util.zip.GZIPOutputStream(bout))
		{
			OutputStream os = GZIPOutputStream(bout);
			IOUtils::copy(is, os);
		}

		return bout->toByteArray();
	}

	std::vector<signed char> GZip::decompress(std::vector<signed char> &bytes, int len)
	{
		std::shared_ptr<ByteArrayOutputStream> os = std::make_shared<ByteArrayOutputStream>();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.InputStream is = new java.util.zip.GZIPInputStream(new java.io.ByteArrayInputStream(bytes, 0, len)))
		{
			InputStream is = GZIPInputStream(std::make_shared<ByteArrayInputStream>(bytes, 0, len));
			IOUtils::copy(is, os);
		}

		return os->toByteArray();
	}
}
