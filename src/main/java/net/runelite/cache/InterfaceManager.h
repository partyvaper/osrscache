#pragma once

#include "definitions/InterfaceDefinition.h"
#include "definitions/exporters/InterfaceExporter.h"
#include "definitions/loaders/InterfaceLoader.h"
#include "fs/Archive.h"
#include "fs/ArchiveFiles.h"
#include "fs/FSFile.h"
#include "fs/Index.h"
#include "fs/Storage.h"
#include "fs/Store.h"
#include "util/Namer.h"
#include <string>
#include <vector>
#include <memory>

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
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
	using InterfaceDefinition = net::runelite::cache::definitions::InterfaceDefinition;
	using Store = net::runelite::cache::fs::Store;
	using Namer = net::runelite::cache::util::Namer;

	class InterfaceManager : public std::enable_shared_from_this<InterfaceManager>
	{
	private:
		const std::shared_ptr<Store> store;
		std::vector<std::vector<std::shared_ptr<InterfaceDefinition>>> interfaces;
		const std::shared_ptr<Namer> namer = std::make_shared<Namer>();

	public:
		InterfaceManager(std::shared_ptr<Store> store);

		virtual void load();

		virtual int getNumInterfaceGroups();

		virtual int getNumChildren(int groupId);

		virtual std::vector<std::shared_ptr<InterfaceDefinition>> getIntefaceGroup(int groupId);

		virtual std::shared_ptr<InterfaceDefinition> getInterface(int groupId, int childId);

		virtual std::vector<std::vector<std::shared_ptr<InterfaceDefinition>>> getInterfaces();

		virtual void export_Keyword(std::shared_ptr<File> out);

		virtual void java(std::shared_ptr<File> java);
	};

}
