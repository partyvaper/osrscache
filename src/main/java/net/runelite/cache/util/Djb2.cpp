#include "Djb2.h"

namespace net::runelite::cache::util
{

	int Djb2::hash(const std::wstring &str)
	{
		int hash = 0;
		for (int i = 0; i < str.length(); i++)
		{
			hash = str[i] + ((hash << 5) - hash);
		}
		return hash;
	}
}
