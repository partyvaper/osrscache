#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "tangible_exception_helper.h"
#include <memory>
#include "../../../../../../../tangible_string_helper.h"

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace net::runelite::cache::util { class SimpleRaster; }
namespace net::runelite::cache::util { class FileDataBuffer; }

namespace net::runelite::cache::util
{

	/*
	 * This class is part of MCFS (Mission Control - Flight Software) a development
	 * of Team Puli Space, official Google Lunar XPRIZE contestant.
	 * This class is released under Creative Commons CC0.
	 * @author Zsolt Pocze, Dimitry Polivaev
	 * Please like us on facebook, and/or join our Small Step Club.
	 * http://www.pulispace.com
	 * https://www.facebook.com/pulispace
	 * http://nyomdmegteis.hu/en/
	 */

	using Point = java::awt::Point;
	using Rectangle = java::awt::Rectangle;
	using BufferedImage = java::awt::image::BufferedImage;
	using ColorModel = java::awt::image::ColorModel;
	using DataBuffer = java::awt::image::DataBuffer;
	using RenderedImage = java::awt::image::RenderedImage;
	using SampleModel = java::awt::image::SampleModel;
	using WritableRaster = java::awt::image::WritableRaster;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using RandomAccessFile = java::io::RandomAccessFile;
	using MappedByteBuffer = java::nio::MappedByteBuffer;
	using HashSet = java::util::HashSet;
	using Hashtable = java::util::Hashtable;
	using Callable = java::util::concurrent::Callable;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Slf4j public class BigBufferedImage extends java.awt.image.BufferedImage
	class BigBufferedImage : public BufferedImage
	{
	private:
		static const std::wstring TMP_DIR;
		static constexpr int MAX_PIXELS_IN_MEMORY = 1024 * 1024;

	public:
		static std::shared_ptr<BufferedImage> create(int width, int height, int imageType);

		static std::shared_ptr<BufferedImage> create(std::shared_ptr<File> inputFile, int imageType);

	private:
		static std::shared_ptr<BufferedImage> createBigBufferedImage(std::shared_ptr<File> tempDir, int width, int height, int imageType);

	private:
		class ImagePartLoader : public std::enable_shared_from_this<ImagePartLoader>, public Callable<std::shared_ptr<ImagePartLoader>>
		{
		private:
			const int y;
			const std::shared_ptr<BufferedImage> image;
			const std::shared_ptr<Rectangle> region;
			const std::shared_ptr<File> file;

		public:
			ImagePartLoader(int y, int width, int height, std::shared_ptr<File> file, std::shared_ptr<BufferedImage> image);

			std::shared_ptr<ImagePartLoader> call() override;
		};

	private:
		template<typename T1, typename T2>
		BigBufferedImage(std::shared_ptr<ColorModel> cm, std::shared_ptr<SimpleRaster> raster, bool isRasterPremultiplied, std::unordered_map<T1, T2> properties) : BufferedImage(cm, raster, isRasterPremultiplied, properties)
		{
		}

	public:
		virtual void dispose();

		static void dispose(std::shared_ptr<RenderedImage> image);

	private:
		class SimpleRaster : public WritableRaster
		{
		public:
			SimpleRaster(std::shared_ptr<SampleModel> sampleModel, std::shared_ptr<FileDataBuffer> dataBuffer, std::shared_ptr<Point> origin);

			virtual void dispose();

		protected:
			std::shared_ptr<SimpleRaster> shared_from_this()
			{
				return std::static_pointer_cast<SimpleRaster>(java::awt::image::WritableRaster::shared_from_this());
			}
		};

	private:
		class FileDataBufferDeleterHook final : public Thread
		{
			private:
				class StaticConstructor : public std::enable_shared_from_this<StaticConstructor>
				{
				public:
					StaticConstructor();
				};

			private:
				static FileDataBufferDeleterHook::StaticConstructor staticConstructor;


			static const std::unordered_set<std::shared_ptr<FileDataBuffer>> undisposedBuffers;

		public:
			void run() override;

		protected:
			std::shared_ptr<FileDataBufferDeleterHook> shared_from_this()
			{
				return std::static_pointer_cast<FileDataBufferDeleterHook>(Thread::shared_from_this());
			}
		};

	private:
		class FileDataBuffer : public DataBuffer
		{
		private:
			const std::wstring id = L"buffer-" + System::currentTimeMillis() + L"-" + std::to_wstring(static_cast<int>(Math::random() * 1000));
			std::shared_ptr<File> dir;
			std::wstring path;
			std::vector<std::shared_ptr<File>> files;
			std::vector<std::shared_ptr<RandomAccessFile>> accessFiles;
			std::vector<std::shared_ptr<MappedByteBuffer>> buffer;

		public:
			FileDataBuffer(std::shared_ptr<File> dir, int size);

			FileDataBuffer(std::shared_ptr<File> dir, int size, int numBanks);

		private:
			void init();

		public:
			int getElem(int bank, int i) override;

			void setElem(int bank, int i, int val) override;

		protected:
//JAVA TO C++ CONVERTER WARNING: There is no equivalent in C++ to finalizer methods:
			void finalize();

		public:
			virtual void dispose();

		private:
			class ThreadAnonymousInnerClass : public Thread
			{
			private:
				std::shared_ptr<FileDataBuffer> outerInstance;

			public:
				ThreadAnonymousInnerClass(std::shared_ptr<FileDataBuffer> outerInstance);

				void run() override;

			protected:
				std::shared_ptr<ThreadAnonymousInnerClass> shared_from_this()
				{
					return std::static_pointer_cast<ThreadAnonymousInnerClass>(Thread::shared_from_this());
				}
			};

		private:
			void disposeNow();


		protected:
			std::shared_ptr<FileDataBuffer> shared_from_this()
			{
				return std::static_pointer_cast<FileDataBuffer>(java::awt::image::DataBuffer::shared_from_this());
			}
		};

	protected:
		std::shared_ptr<BigBufferedImage> shared_from_this()
		{
			return std::static_pointer_cast<BigBufferedImage>(java::awt::image::BufferedImage::shared_from_this());
		}
	};
}
