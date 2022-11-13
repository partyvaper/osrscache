#pragma once

#include "../../../../../../../main/java/net/runelite/cache/IndexType.h"
#include "../../StoreLocation.h"
#include "../../../../../../../main/java/net/runelite/cache/definitions/ScriptDefinition.h"
#include "../../../../../../../main/java/net/runelite/cache/definitions/loaders/ScriptLoader.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/Archive.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/Index.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/Storage.h"
#include "../../../../../../../main/java/net/runelite/cache/fs/Store.h"
#include <string>
#include <vector>
#include <memory>

/*
 * Copyright (c) 2016-2017, Adam <Adam@sigterm.info>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
namespace net::runelite::cache::script::disassembler
{

	using IOException = java::io::IOException;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class DisassemblerTest : public std::enable_shared_from_this<DisassemblerTest>
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

	public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Rule public org.junit.rules.TemporaryFolder folder = net.runelite.cache.StoreLocation.getTemporaryFolder();
		std::shared_ptr<TemporaryFolder> folder = StoreLocation::getTemporaryFolder();

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test() throws java.io.IOException
		virtual void test();
	};

}
