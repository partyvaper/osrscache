#include "Cache.h"
#include "ItemManager.h"
#include "NpcManager.h"
#include "ObjectManager.h"
#include "SpriteManager.h"

namespace net::runelite::cache
{
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Store = net::runelite::cache::fs::Store;
	using CommandLine = org::apache::commons::cli::CommandLine;
	using CommandLineParser = org::apache::commons::cli::CommandLineParser;
	using DefaultParser = org::apache::commons::cli::DefaultParser;
	using Options = org::apache::commons::cli::Options;
	using ParseException = org::apache::commons::cli::ParseException;

	void Cache::main(std::vector<std::wstring> &args)
	{
		std::shared_ptr<Options> options = std::make_shared<Options>();

		options->addOption(L"c", L"cache", true, L"cache base");

		options->addOption(nullptr, L"items", true, L"directory to dump items to");
		options->addOption(nullptr, L"npcs", true, L"directory to dump npcs to");
		options->addOption(nullptr, L"objects", true, L"directory to dump objects to");
		options->addOption(nullptr, L"sprites", true, L"directory to dump sprites to");

		std::shared_ptr<CommandLineParser> parser = std::make_shared<DefaultParser>();
		std::shared_ptr<CommandLine> cmd;
		try
		{
			cmd = parser->parse(options, args);
		}
		catch (const ParseException &ex)
		{
			System::err::println(L"Error parsing command line options: " + ex->getMessage());
			exit(-1);
			return;
		}

		std::wstring cache = cmd->getOptionValue(L"cache");

		std::shared_ptr<Store> store = loadStore(cache);

		if (cmd->hasOption(L"items"))
		{
			std::wstring itemdir = cmd->getOptionValue(L"items");

			if (itemdir == L"")
			{
				System::err::println(L"Item directory must be specified");
				return;
			}

			std::wcout << L"Dumping items to " << itemdir << std::endl;
			dumpItems(store, std::make_shared<File>(itemdir));
		}
		else if (cmd->hasOption(L"npcs"))
		{
			std::wstring npcdir = cmd->getOptionValue(L"npcs");

			if (npcdir == L"")
			{
				System::err::println(L"NPC directory must be specified");
				return;
			}

			std::wcout << L"Dumping npcs to " << npcdir << std::endl;
			dumpNpcs(store, std::make_shared<File>(npcdir));
		}
		else if (cmd->hasOption(L"objects"))
		{
			std::wstring objectdir = cmd->getOptionValue(L"objects");

			if (objectdir == L"")
			{
				System::err::println(L"Object directory must be specified");
				return;
			}

			std::wcout << L"Dumping objects to " << objectdir << std::endl;
			dumpObjects(store, std::make_shared<File>(objectdir));
		}
		else if (cmd->hasOption(L"sprites"))
		{
			std::wstring spritedir = cmd->getOptionValue(L"sprites");

			if (spritedir == L"")
			{
				System::err::println(L"Sprite directory must be specified");
				return;
			}

			std::wcout << L"Dumping sprites to " << spritedir << std::endl;
			dumpSprites(store, std::make_shared<File>(spritedir));
		}
		else
		{
			System::err::println(L"Nothing to do");
		}
	}

	std::shared_ptr<Store> Cache::loadStore(const std::wstring &cache)
	{
		std::shared_ptr<Store> store = std::make_shared<Store>(std::make_shared<File>(cache));
		store->load();
		return store;
	}

	void Cache::dumpItems(std::shared_ptr<Store> store, std::shared_ptr<File> itemdir)
	{
		std::shared_ptr<ItemManager> dumper = std::make_shared<ItemManager>(store);
		dumper->load();
		dumper->export_Keyword(itemdir);
		dumper->java(itemdir);
	}

	void Cache::dumpNpcs(std::shared_ptr<Store> store, std::shared_ptr<File> npcdir)
	{
		std::shared_ptr<NpcManager> dumper = std::make_shared<NpcManager>(store);
		dumper->load();
		dumper->dump(npcdir);
		dumper->java(npcdir);
	}

	void Cache::dumpObjects(std::shared_ptr<Store> store, std::shared_ptr<File> objectdir)
	{
		std::shared_ptr<ObjectManager> dumper = std::make_shared<ObjectManager>(store);
		dumper->load();
		dumper->dump(objectdir);
		dumper->java(objectdir);
	}

	void Cache::dumpSprites(std::shared_ptr<Store> store, std::shared_ptr<File> spritedir)
	{
		std::shared_ptr<SpriteManager> dumper = std::make_shared<SpriteManager>(store);
		dumper->load();
		dumper->export_Keyword(spritedir);
	}
}
