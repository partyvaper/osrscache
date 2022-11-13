#pragma once

#include <string>
#include <vector>
#include "MapImageDumper.h"

int main(int argc, char **argv)
{
	std::vector<std::wstring> args(argv + 1, argv + argc);
	net::runelite::cache::MapImageDumper::main(args);
}

