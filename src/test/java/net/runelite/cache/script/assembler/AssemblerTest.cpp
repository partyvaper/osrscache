#include "AssemblerTest.h"
#include "../../../../../../../main/java/net/runelite/cache/script/assembler/Assembler.h"

namespace net::runelite::cache::script::assembler
{
	using InputStream = java::io::InputStream;
	using StandardCharsets = java::nio::charset::StandardCharsets;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using Instructions = net::runelite::cache::script::Instructions;
	using Disassembler = net::runelite::cache::script::disassembler::Disassembler;
	using IOUtils = org::apache::commons::compress::utils::IOUtils;
	using Assert = org::junit::Assert;
	using Test = org::junit::Test;
	using RunWith = org::junit::runner::RunWith;
	using Parameterized = org::junit::runners::Parameterized;
	using Parameter = org::junit::runners::Parameterized::Parameter;
	using Parameters = org::junit::runners::Parameterized::Parameters;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> AssemblerTest::logger = org::slf4j::LoggerFactory::getLogger(AssemblerTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Parameters public static String[] scripts()
	std::vector<std::wstring> AssemblerTest::scripts()
	{
		return std::vector<std::wstring> {L"91.rs2asm", L"681.rs2asm", L"Unicode.rs2asm"};
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testAssemble() throws Exception
	void AssemblerTest::testAssemble()
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		std::shared_ptr<InputStream> in = AssemblerTest::class->getResourceAsStream(script);
		Assert::assertNotNull(in);

		std::shared_ptr<Instructions> instructions = std::make_shared<Instructions>();
		instructions->init();

		std::shared_ptr<Assembler> assembler = std::make_shared<Assembler>(instructions);
		std::shared_ptr<ScriptDefinition> script = assembler->assemble(in);

		// compare with disassembler
		std::shared_ptr<Disassembler> disassembler = std::make_shared<Disassembler>();
		std::wstring out = disassembler->disassemble(script);

//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		in = AssemblerTest::class->getResourceAsStream(this->script);
		Assert::assertNotNull(in);

		std::wstring original = (std::wstring(IOUtils::toByteArray(in), StandardCharsets::UTF_8))->replaceAll(L"\r\n", L"\n");

		logger->info(original);
		logger->info(L"-----------------------");
		logger->info(out);

		Assert::assertEquals(original, out);
	}
}
