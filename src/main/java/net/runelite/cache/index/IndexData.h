#pragma once

#include "../io/InputStream.h"
#include "../io/OutputStream.h"
#include "ArchiveData.h"
#include <vector>
#include <stdexcept>
#include <cassert>
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
namespace net::runelite::cache::index
{


	class IndexData : public std::enable_shared_from_this<IndexData>
	{
	private:
		int protocol = 0;
		int revision = 0;
		bool named = false;
		std::vector<std::shared_ptr<ArchiveData>> archives;

	public:
		virtual void load(std::vector<signed char> &data);

		virtual std::vector<signed char> writeIndexData();

		virtual int getProtocol();

		virtual void setProtocol(int protocol);

		virtual int getRevision();

		virtual void setRevision(int revision);

		virtual bool isNamed();

		virtual void setNamed(bool named);

		virtual std::vector<std::shared_ptr<ArchiveData>> getArchives();

		virtual void setArchives(std::vector<std::shared_ptr<ArchiveData>> &archives);
	};

}
