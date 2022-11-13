#include "Namer.h"

namespace net::runelite::cache::util
{
	using HashSet = java::util::HashSet;
	using Set = java::util::Set;

	std::wstring Namer::name(const std::wstring &name, int id)
	{
		name = sanitize(name);

		if (name == L"")
		{
			return L"";
		}

		if (used->contains(name))
		{
			name = name + L"_" + std::to_wstring(id);
			assert(!used->contains(name));
		}

		used->add(name);

		return name;
	}

	std::wstring Namer::sanitize(const std::wstring &in)
	{
		std::wstring s = StringHelper::toUpper(removeTags(in))->replace(L' ', L'_').replaceAll(L"[^a-zA-Z0-9_]", L"");
		if (s.isEmpty())
		{
			return L"";
		}
		if (std::isdigit(s[0]))
		{
			return L"_" + s;
		}
		else
		{
			return s;
		}
	}

	std::wstring Namer::removeTags(const std::wstring &str)
	{
		std::shared_ptr<StringBuilder> builder = std::make_shared<StringBuilder>(str.length());
		bool inTag = false;

		for (int i = 0; i < str.length(); i++)
		{
			wchar_t currentChar = str[i];

			if (currentChar == L'<')
			{
				inTag = true;
			}
			else if (currentChar == L'>')
			{
				inTag = false;
			}
			else if (!inTag)
			{
				builder->append(currentChar);
			}
		}

		return builder->toString();
	}
}
