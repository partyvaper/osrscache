#pragma once

#include <string>
#include "tangible_exception_helper.h"
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
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class StoreLocation : public std::enable_shared_from_this<StoreLocation>
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

		static constexpr int NUM_INDEXES = 16;

	public:
		static std::shared_ptr<File> LOCATION;
	private:
		static std::shared_ptr<File> TMP;

		private:
			class StaticConstructor : public std::enable_shared_from_this<StaticConstructor>
			{
			public:
				StaticConstructor();
			};

		private:
			static StoreLocation::StaticConstructor staticConstructor;


		static std::shared_ptr<File> setupCacheDir();

	public:
		static std::shared_ptr<TemporaryFolder> getTemporaryFolder();

	private:
		class TemporaryFolderAnonymousInnerClass : public TemporaryFolder
		{
		public:
			void after() override;

		protected:
			std::shared_ptr<TemporaryFolderAnonymousInnerClass> shared_from_this()
			{
				return std::static_pointer_cast<TemporaryFolderAnonymousInnerClass>(org::junit::rules::TemporaryFolder::shared_from_this());
			}
		};
	};

}