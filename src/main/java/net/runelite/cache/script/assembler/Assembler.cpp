#include "Assembler.h"
#include "LexerErrorListener.h"
#include "LabelVisitor.h"
#include "ScriptWriter.h"

namespace net::runelite::cache::script::assembler
{
	using IOException = java::io::IOException;
	using InputStream = java::io::InputStream;
	using InputStreamReader = java::io::InputStreamReader;
	using StandardCharsets = java::nio::charset::StandardCharsets;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using Instructions = net::runelite::cache::script::Instructions;
	using ProgContext = net::runelite::cache::script::assembler::rs2asmParser::ProgContext;
	using ANTLRInputStream = org::antlr::v4::runtime::ANTLRInputStream;
	using CommonTokenStream = org::antlr::v4::runtime::CommonTokenStream;
	using ParseTreeWalker = org::antlr::v4::runtime::tree::ParseTreeWalker;

	Assembler::Assembler(std::shared_ptr<Instructions> instructions) : instructions(instructions)
	{
	}

	std::shared_ptr<ScriptDefinition> Assembler::assemble(std::shared_ptr<InputStream> in)
	{
		// Get our lexer
		std::shared_ptr<rs2asmLexer> lexer = std::make_shared<rs2asmLexer>(std::make_shared<ANTLRInputStream>(std::make_shared<InputStreamReader>(in, StandardCharsets::UTF_8)));

		std::shared_ptr<LexerErrorListener> errorListener = std::make_shared<LexerErrorListener>();
		lexer->addErrorListener(errorListener);

		// Get a list of matched tokens
		std::shared_ptr<CommonTokenStream> tokens = std::make_shared<CommonTokenStream>(lexer);

		// Pass the tokens to the parser
		std::shared_ptr<rs2asmParser> parser = std::make_shared<rs2asmParser>(tokens);

		// Specify our entry point
		std::shared_ptr<ProgContext> progContext = parser->prog();

		if (errorListener->getErrors() > 0)
		{
			throw std::runtime_error("syntax error");
		}

		// Walk it and attach our listener
		std::shared_ptr<ParseTreeWalker> walker = std::make_shared<ParseTreeWalker>();

		// walk through first and resolve labels
		std::shared_ptr<LabelVisitor> labelVisitor = std::make_shared<LabelVisitor>();
		walker->walk(labelVisitor, progContext);

		std::shared_ptr<ScriptWriter> listener = std::make_shared<ScriptWriter>(instructions, labelVisitor);
		walker->walk(listener, progContext);

		return listener->buildScript();
	}
}
