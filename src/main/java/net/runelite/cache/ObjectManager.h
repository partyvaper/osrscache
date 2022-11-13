#pragma once

#include "definitions/ObjectDefinition.h"
#include "definitions/exporters/ObjectExporter.h"
#include "definitions/loaders/ObjectLoader.h"
#include "fs/Archive.h"
#include "fs/ArchiveFiles.h"
#include "fs/FSFile.h"
#include "fs/Index.h"
#include "fs/Storage.h"
#include "fs/Store.h"
#include "util/IDClass.h"
#include <unordered_map>
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
namespace net::runelite::cache
{

	using File = java::io::File;
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using ObjectDefinition = net::runelite::cache::definitions::ObjectDefinition;
	using Store = net::runelite::cache::fs::Store;

	class ObjectManager : public std::enable_shared_from_this<ObjectManager>
	{
	private:
		const std::shared_ptr<Store> store;
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<int, net.runelite.cache.definitions.ObjectDefinition> objects = new java.util.HashMap<>();
		std::unordered_map<int, std::shared_ptr<ObjectDefinition>> objects = std::unordered_map<int, std::shared_ptr<ObjectDefinition>>();

	public:
		ObjectManager(std::shared_ptr<Store> store);

		virtual void load();

		virtual std::shared_ptr<Collection<std::shared_ptr<ObjectDefinition>>> getObjects();

		virtual std::shared_ptr<ObjectDefinition> getObject(int id);

		virtual void dump(std::shared_ptr<File> out);

		virtual void java(std::shared_ptr<File> java);
	};

}
