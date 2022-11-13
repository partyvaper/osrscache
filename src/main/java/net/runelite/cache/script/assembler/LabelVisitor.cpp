#include "LabelVisitor.h"

namespace net::runelite::cache::script::assembler
{
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> LabelVisitor::logger = org::slf4j::LoggerFactory::getLogger(LabelVisitor::class);

	void LabelVisitor::exitInstruction(std::shared_ptr<rs2asmParser::InstructionContext> ctx)
	{
		++pos;
	}

	void LabelVisitor::enterLabel(std::shared_ptr<rs2asmParser::LabelContext> ctx)
	{
		std::wstring text = ctx->getText();
		text = text.substr(0, text.length() - 1); // remove trailing :

		logger->debug(L"Label {} is on instruction {}", text, pos);

		map.emplace(text, pos);
	}

	std::optional<int> LabelVisitor::getInstructionForLabel(const std::wstring &label)
	{
		return map[label];
	}
}
