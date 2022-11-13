#include "LookupCase.h"

namespace net::runelite::cache::script::assembler
{

	int LookupCase::getValue()
	{
		return value;
	}

	void LookupCase::setValue(int value)
	{
		this->value = value;
	}

	int LookupCase::getOffset()
	{
		return offset;
	}

	void LookupCase::setOffset(int offset)
	{
		this->offset = offset;
	}
}
