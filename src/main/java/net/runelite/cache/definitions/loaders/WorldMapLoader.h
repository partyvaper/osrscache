#pragma once

#include "../WorldMapDefinition.h"
#include "../WorldMapType0.h"
#include "../WorldMapType1.h"
#include "../WorldMapType2.h"
#include "../WorldMapType3.h"
#include "../WorldMapTypeBase.h"
#include "../../io/InputStream.h"
#include "../../region/Position.h"
#include <vector>
#include <list>
#include "tangible_exception_helper.h"
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
namespace net::runelite::cache::definitions::loaders
{

	using WorldMapDefinition = net::runelite::cache::definitions::WorldMapDefinition;
	using WorldMapTypeBase = net::runelite::cache::definitions::WorldMapTypeBase;
	using InputStream = net::runelite::cache::io::InputStream;

	class WorldMapLoader : public std::enable_shared_from_this<WorldMapLoader>
	{
	public:
		virtual std::shared_ptr<WorldMapDefinition> load(std::vector<signed char> &b, int fileId);

	private:
		std::shared_ptr<WorldMapTypeBase> loadType(std::shared_ptr<InputStream> var1);

		std::shared_ptr<WorldMapTypeBase> load0(std::shared_ptr<InputStream> in);

		std::shared_ptr<WorldMapTypeBase> load1(std::shared_ptr<InputStream> in);

		std::shared_ptr<WorldMapTypeBase> load2(std::shared_ptr<InputStream> in);

		std::shared_ptr<WorldMapTypeBase> load3(std::shared_ptr<InputStream> in);
	};

}
