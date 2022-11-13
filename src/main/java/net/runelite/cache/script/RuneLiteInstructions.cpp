#include "RuneLiteInstructions.h"

namespace net::runelite::cache::script
{

	void RuneLiteInstructions::init()
	{
		Instructions::init();
		add(RUNELITE_EXECUTE, L"runelite_callback");
	}
}
