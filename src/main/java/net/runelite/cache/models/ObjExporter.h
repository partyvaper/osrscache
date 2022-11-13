#pragma once

#include "../TextureManager.h"
#include "../definitions/ModelDefinition.h"
#include "../definitions/TextureDefinition.h"
#include "JagexColor.h"
#include <vector>
#include <cassert>
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
namespace net::runelite::cache::models
{

	using PrintWriter = java::io::PrintWriter;
	using TextureManager = net::runelite::cache::TextureManager;
	using ModelDefinition = net::runelite::cache::definitions::ModelDefinition;

	class ObjExporter : public std::enable_shared_from_this<ObjExporter>
	{
	private:
		static constexpr double BRIGHTNESS = JagexColor::BRIGHTNESS_MIN;

		const std::shared_ptr<TextureManager> textureManager;
		const std::shared_ptr<ModelDefinition> model;

	public:
		ObjExporter(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<ModelDefinition> model);

		virtual void export_Keyword(std::shared_ptr<PrintWriter> objWriter, std::shared_ptr<PrintWriter> mtlWriter);
	};

}
