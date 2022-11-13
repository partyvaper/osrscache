#pragma once

#include "KeyProvider.h"
#include "XteaKey.h"
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
namespace net::runelite::cache::util
{

	using InputStream = java::io::InputStream;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class XteaKeyManager : public std::enable_shared_from_this<XteaKeyManager>, public KeyProvider
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<int, int[]> keys = new java.util.HashMap<>();
		std::unordered_map<int, std::vector<int>> keys = std::unordered_map<int, std::vector<int>>();

	public:
		virtual void loadKeys(std::shared_ptr<InputStream> in);

	private:
		class TypeTokenAnonymousInnerClass : public TypeToken<std::vector<std::shared_ptr<XteaKey>>>
		{
		private:
			std::shared_ptr<XteaKeyManager> outerInstance;

		public:
			TypeTokenAnonymousInnerClass(std::shared_ptr<XteaKeyManager> outerInstance);


		protected:
			std::shared_ptr<TypeTokenAnonymousInnerClass> shared_from_this()
			{
				return std::static_pointer_cast<TypeTokenAnonymousInnerClass>(com::google::gson::reflect::TypeToken::shared_from_this());
			}
		};

	public:
		std::vector<int> getKey(int region) override;
	};

}
