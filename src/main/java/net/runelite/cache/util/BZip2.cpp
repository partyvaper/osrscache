#include "BZip2.h"

namespace net::runelite::cache::util
{
	using ByteArrayInputStream = java::io::ByteArrayInputStream;
	using ByteArrayOutputStream = java::io::ByteArrayOutputStream;
	using IOException = java::io::IOException;
	using InputStream = java::io::InputStream;
	using OutputStream = java::io::OutputStream;
	using Arrays = java::util::Arrays;
	using BZip2CompressorInputStream = org::apache::commons::compress::compressors::bzip2::BZip2CompressorInputStream;
	using BZip2CompressorOutputStream = org::apache::commons::compress::compressors::bzip2::BZip2CompressorOutputStream;
	using IOUtils = org::apache::commons::compress::utils::IOUtils;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> BZip2::logger = org::slf4j::LoggerFactory::getLogger(BZip2::class);
const std::vector<signed char> BZip2::BZIP_HEADER = std::vector<signed char> {L'B', L'Z', L'h', L'1'};

	std::vector<signed char> BZip2::compress(std::vector<signed char> &bytes)
	{
		std::shared_ptr<InputStream> is = std::make_shared<ByteArrayInputStream>(bytes);
		std::shared_ptr<ByteArrayOutputStream> bout = std::make_shared<ByteArrayOutputStream>();
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.OutputStream os = new org.apache.commons.compress.compressors.bzip2.BZip2CompressorOutputStream(bout, 1))
		{
			OutputStream os = BZip2CompressorOutputStream(bout, 1);
			IOUtils::copy(is, os);
		}

		std::vector<signed char> out = bout->toByteArray();

		assert(BZIP_HEADER[0] == out[0]);
		assert(BZIP_HEADER[1] == out[1]);
		assert(BZIP_HEADER[2] == out[2]);
		assert(BZIP_HEADER[3] == out[3]);

		return std::vector<signed char>(out.cbegin() + BZIP_HEADER.size(), out.cend()); // remove header..
	}

	std::vector<signed char> BZip2::decompress(std::vector<signed char> &bytes, int len)
	{
		std::vector<signed char> data(len + BZIP_HEADER.size());

		// add header
		std::copy_n(BZIP_HEADER.begin(), BZIP_HEADER.size(), data.begin());
		std::copy_n(bytes.begin(), len, data.begin() + BZIP_HEADER.size());

		std::shared_ptr<ByteArrayOutputStream> os = std::make_shared<ByteArrayOutputStream>();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.InputStream is = new org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream(new java.io.ByteArrayInputStream(data)))
		{
			InputStream is = BZip2CompressorInputStream(std::make_shared<ByteArrayInputStream>(data));
			IOUtils::copy(is, os);
		}

		return os->toByteArray();
	}
}
