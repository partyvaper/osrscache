#include "ScriptSaverTest.h"
#include "../../../../../../../main/java/net/runelite/cache/definitions/savers/ScriptSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using IOException = java::io::IOException;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using ScriptLoader = net::runelite::cache::definitions::loaders::ScriptLoader;
	using Instructions = net::runelite::cache::script::Instructions;
	using Assembler = net::runelite::cache::script::assembler::Assembler;
//	import static org.junit.Assert.assertEquals;
	using Test = org::junit::Test;
const std::wstring ScriptSaverTest::SCRIPT_RESOURCE = L"/net/runelite/cache/script/assembler/91.rs2asm";
const std::wstring ScriptSaverTest::SCRIPT_RESOURCE_UNICODE = L"/net/runelite/cache/script/assembler/Unicode.rs2asm";

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testSave() throws java.io.IOException
	void ScriptSaverTest::testSave()
	{
		std::shared_ptr<Instructions> instructions = std::make_shared<Instructions>();
		instructions->init();
		std::shared_ptr<ScriptDefinition> script = (std::make_shared<Assembler>(instructions))->assemble(getClass().getResourceAsStream(SCRIPT_RESOURCE));
		std::vector<signed char> saved = (std::make_shared<ScriptSaver>())->save(script);
		std::shared_ptr<ScriptDefinition> loadedScripot = (std::make_shared<ScriptLoader>())->load(91, saved);
		assertEquals(script, loadedScripot);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testSaveUnicode() throws java.io.IOException
	void ScriptSaverTest::testSaveUnicode()
	{
		std::shared_ptr<Instructions> instructions = std::make_shared<Instructions>();
		instructions->init();
		std::shared_ptr<ScriptDefinition> script = (std::make_shared<Assembler>(instructions))->assemble(getClass().getResourceAsStream(SCRIPT_RESOURCE_UNICODE));
		std::vector<signed char> saved = (std::make_shared<ScriptSaver>())->save(script);
		std::shared_ptr<ScriptDefinition> loadedScripot = (std::make_shared<ScriptLoader>())->load(1001, saved);
		assertEquals(script, loadedScripot);
	}
}
