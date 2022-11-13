#pragma once

#include "../../sound/SoundEffect1Definition.h"
#include "../../sound/SoundEffect2Definition.h"
#include "../../../io/InputStream.h"
#include "SoundEffect2Loader.h"
#include "SoundEffect3Loader.h"
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
namespace net::runelite::cache::definitions::loaders::sound
{

	using SoundEffect1Definition = net::runelite::cache::definitions::sound::SoundEffect1Definition;
	using InputStream = net::runelite::cache::io::InputStream;

	class SoundEffect1Loader : public std::enable_shared_from_this<SoundEffect1Loader>
	{
	private:
		const std::shared_ptr<SoundEffect2Loader> se2Loader = std::make_shared<SoundEffect2Loader>();
		const std::shared_ptr<SoundEffect3Loader> se3Loader = std::make_shared<SoundEffect3Loader>();

	public:
		virtual std::shared_ptr<SoundEffect1Definition> load(std::shared_ptr<InputStream> in);

	private:
		void load(std::shared_ptr<SoundEffect1Definition> se, std::shared_ptr<InputStream> var1);
	};

}
