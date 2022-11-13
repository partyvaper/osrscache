#include "LookupSwitch.h"

namespace net::runelite::cache::script::assembler
{
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;

	std::vector<std::shared_ptr<LookupCase>> LookupSwitch::getCases()
	{
		return cases;
	}
}
