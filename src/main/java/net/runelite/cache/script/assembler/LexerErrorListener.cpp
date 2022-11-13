#include "LexerErrorListener.h"

namespace net::runelite::cache::script::assembler
{
	using BaseErrorListener = org::antlr::v4::runtime::BaseErrorListener;
	using RecognitionException = org::antlr::v4::runtime::RecognitionException;
	using Recognizer = org::antlr::v4::runtime::Recognizer;

	int LexerErrorListener::getErrors()
	{
		return errors;
	}
}
