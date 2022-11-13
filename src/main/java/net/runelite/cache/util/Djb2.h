#pragma once

#include <string>
#include <memory>

namespace net::runelite::cache::util
{

	/**
	 * An implementation of the {@code djb2} hash function.
	 *
	 * @author Graham
	 * @author `Discardedx2
	 */
	class Djb2 final : public std::enable_shared_from_this<Djb2>
	{
		/**
		 * An implementation of Dan Bernstein's {@code djb2} hash function which
		 * is slightly modified. Instead of the initial hash being 5381, it is
		 * zero.
		 *
		 * @param str The string to hash.
		 * @return The hash code.
		 */
	public:
		static int hash(const std::wstring &str);
	};

}
