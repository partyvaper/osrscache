#include "BigBufferedImage.h"

namespace net::runelite::cache::util
{
	using Point = java::awt::Point;
	using Rectangle = java::awt::Rectangle;
	using ColorSpace = java::awt::color::ColorSpace;
	using BandedSampleModel = java::awt::image::BandedSampleModel;
	using BufferedImage = java::awt::image::BufferedImage;
	using ColorModel = java::awt::image::ColorModel;
	using ComponentColorModel = java::awt::image::ComponentColorModel;
	using DataBuffer = java::awt::image::DataBuffer;
	using Raster = java::awt::image::Raster;
	using RenderedImage = java::awt::image::RenderedImage;
	using SampleModel = java::awt::image::SampleModel;
	using WritableRaster = java::awt::image::WritableRaster;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using RandomAccessFile = java::io::RandomAccessFile;
	using MappedByteBuffer = java::nio::MappedByteBuffer;
	using FileChannel = java::nio::channels::FileChannel;
	using ArrayList = java::util::ArrayList;
	using HashSet = java::util::HashSet;
	using Hashtable = java::util::Hashtable;
	using Iterator = java::util::Iterator;
	using List = java::util::List;
	using Callable = java::util::concurrent::Callable;
	using ExecutorService = java::util::concurrent::ExecutorService;
	using Executors = java::util::concurrent::Executors;
	using ImageIO = javax::imageio::ImageIO;
	using ImageReadParam = javax::imageio::ImageReadParam;
	using ImageReader = javax::imageio::ImageReader;
	using ImageInputStream = javax::imageio::stream::ImageInputStream;
	using Slf4j = lombok::extern_Keyword::slf4j::Slf4j;
const std::wstring BigBufferedImage::TMP_DIR = System::getProperty(L"java.io.tmpdir");

	std::shared_ptr<BufferedImage> BigBufferedImage::create(int width, int height, int imageType)
	{
		if (width * height > MAX_PIXELS_IN_MEMORY)
		{
			try
			{
				constexpr std::shared_ptr<File> tempDir = std::make_shared<File>(TMP_DIR);
				return createBigBufferedImage(tempDir, width, height, imageType);
			}
			catch (const IOException &e)
			{
				throw std::runtime_error(e);
			}
		}
		else
		{
			return std::make_shared<BufferedImage>(width, height, imageType);
		}
	}

	std::shared_ptr<BufferedImage> BigBufferedImage::create(std::shared_ptr<File> inputFile, int imageType)
	{
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (javax.imageio.stream.ImageInputStream stream = javax.imageio.ImageIO.createImageInputStream(inputFile))
		{
			ImageInputStream stream = ImageIO::createImageInputStream(inputFile);
			Iterator<std::shared_ptr<ImageReader>> readers = ImageIO::getImageReaders(stream);
			if (readers->hasNext())
			{
				try
				{
					std::shared_ptr<ImageReader> reader = readers->next();
					reader->setInput(stream, true, true);
					int width = reader->getWidth(reader->getMinIndex());
					int height = reader->getHeight(reader->getMinIndex());
					std::shared_ptr<BufferedImage> image = create(width, height, imageType);
					int cores = std::max(1, Runtime::getRuntime().availableProcessors() / 2);
					int block = std::min(MAX_PIXELS_IN_MEMORY / cores / width, static_cast<int>(std::ceil(height / static_cast<double>(cores))));
					std::shared_ptr<ExecutorService> generalExecutor = Executors::newFixedThreadPool(cores);
					std::vector<Callable<std::shared_ptr<ImagePartLoader>>> partLoaders;
					for (int y = 0; y < height; y += block)
					{
						partLoaders.push_back(std::make_shared<ImagePartLoader>(y, width, std::min(block, height - y), inputFile, image));
					}
					generalExecutor->invokeAll(partLoaders);
					generalExecutor->shutdown();
					return image;
				}
				catch (const InterruptedException &ex)
				{
					log::error(nullptr, ex);
				}
			}
		}
		return nullptr;
	}

	std::shared_ptr<BufferedImage> BigBufferedImage::createBigBufferedImage(std::shared_ptr<File> tempDir, int width, int height, int imageType)
	{
		std::shared_ptr<FileDataBuffer> buffer = std::make_shared<FileDataBuffer>(tempDir, width * height, 4);
		std::shared_ptr<ColorModel> colorModel;
		std::shared_ptr<BandedSampleModel> sampleModel;
		switch (imageType)
		{
			case TYPE_INT_RGB:
				colorModel = std::make_shared<ComponentColorModel>(ColorSpace::getInstance(ColorSpace::CS_sRGB), std::vector<int>{8, 8, 8, 0}, false, false, ComponentColorModel::TRANSLUCENT, DataBuffer::TYPE_BYTE);
				sampleModel = std::make_shared<BandedSampleModel>(DataBuffer::TYPE_BYTE, width, height, 3);
				break;
			case TYPE_INT_ARGB:
				colorModel = std::make_shared<ComponentColorModel>(ColorSpace::getInstance(ColorSpace::CS_sRGB), std::vector<int>{8, 8, 8, 8}, true, false, ComponentColorModel::TRANSLUCENT, DataBuffer::TYPE_BYTE);
				sampleModel = std::make_shared<BandedSampleModel>(DataBuffer::TYPE_BYTE, width, height, 4);
				break;
			default:
				throw std::invalid_argument(StringHelper::wstring_to_string(L"Unsupported image type: " + std::to_wstring(imageType)));
		}
		std::shared_ptr<SimpleRaster> raster = std::make_shared<SimpleRaster>(sampleModel, buffer, std::make_shared<Point>(0, 0));
//JAVA TO C++ CONVERTER TODO TASK: Java wildcard generics are not converted to C++:
//ORIGINAL LINE: BigBufferedImage image = new BigBufferedImage(colorModel, raster, colorModel.isAlphaPremultiplied(), null);
		std::shared_ptr<BigBufferedImage> image = std::make_shared<BigBufferedImage>(colorModel, raster, colorModel->isAlphaPremultiplied(), std::unordered_map<?,  ?>());
		return image;
	}

	BigBufferedImage::ImagePartLoader::ImagePartLoader(int y, int width, int height, std::shared_ptr<File> file, std::shared_ptr<BufferedImage> image) : y(y), image(image), region(std::make_shared<Rectangle>(0, y, width, height)), file(file)
	{
	}

	std::shared_ptr<ImagePartLoader> BigBufferedImage::ImagePartLoader::call()
	{
		Thread::currentThread().setPriority((Thread::MIN_PRIORITY + Thread::NORM_PRIORITY) / 2);
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (javax.imageio.stream.ImageInputStream stream = javax.imageio.ImageIO.createImageInputStream(file);)
		{
			ImageInputStream stream = ImageIO::createImageInputStream(file);
			Iterator<std::shared_ptr<ImageReader>> readers = ImageIO::getImageReaders(stream);
			if (readers->hasNext())
			{
				std::shared_ptr<ImageReader> reader = readers->next();
				reader->setInput(stream, true, true);
				std::shared_ptr<ImageReadParam> param = reader->getDefaultReadParam();
				param->setSourceRegion(region);
				std::shared_ptr<BufferedImage> part = reader->read(0, param);
				std::shared_ptr<Raster> source = part->getRaster();
				std::shared_ptr<WritableRaster> target = image->getRaster();
				target->setRect(0, y, source);
			}
		}
		return ImagePartLoader::this;
	}

	void BigBufferedImage::dispose()
	{
		(std::static_pointer_cast<SimpleRaster>(getRaster()))->dispose();
	}

	void BigBufferedImage::dispose(std::shared_ptr<RenderedImage> image)
	{
		if (std::dynamic_pointer_cast<BigBufferedImage>(image) != nullptr)
		{
			(std::static_pointer_cast<BigBufferedImage>(image))->dispose();
		}
	}

	BigBufferedImage::SimpleRaster::SimpleRaster(std::shared_ptr<SampleModel> sampleModel, std::shared_ptr<FileDataBuffer> dataBuffer, std::shared_ptr<Point> origin) : java::awt::image::WritableRaster(sampleModel, dataBuffer, origin)
	{
	}

	void BigBufferedImage::SimpleRaster::dispose()
	{
		(std::static_pointer_cast<FileDataBuffer>(getDataBuffer()))->dispose();
	}

	BigBufferedImage::FileDataBufferDeleterHook::StaticConstructor::StaticConstructor()
	{
	Runtime::getRuntime().addShutdownHook(std::make_shared<FileDataBufferDeleterHook>());
	}

FileDataBufferDeleterHook::StaticConstructor BigBufferedImage::FileDataBufferDeleterHook::staticConstructor;
const std::unordered_set<std::shared_ptr<FileDataBuffer>> BigBufferedImage::FileDataBufferDeleterHook::undisposedBuffers = std::unordered_set<std::shared_ptr<FileDataBuffer>>();

	void BigBufferedImage::FileDataBufferDeleterHook::run()
	{
		const std::vector<std::shared_ptr<FileDataBuffer>> buffers = undisposedBuffers.toArray(std::vector<std::shared_ptr<FileDataBuffer>>(0));
		for (auto b : buffers)
		{
			b->disposeNow();
		}
	}

	BigBufferedImage::FileDataBuffer::FileDataBuffer(std::shared_ptr<File> dir, int size) : java::awt::image::DataBuffer(TYPE_BYTE, size)
	{
		this->dir = dir;
		init();
	}

	BigBufferedImage::FileDataBuffer::FileDataBuffer(std::shared_ptr<File> dir, int size, int numBanks) : java::awt::image::DataBuffer(TYPE_BYTE, size, numBanks)
	{
		this->dir = dir;
		init();
	}

	void BigBufferedImage::FileDataBuffer::init()
	{
		FileDataBufferDeleterHook::undisposedBuffers.add(shared_from_this());
		if (dir == nullptr)
		{
			dir = std::make_shared<File>(L".");
		}
		if (!dir->exists())
		{
			throw std::runtime_error(StringHelper::wstring_to_string(L"FileDataBuffer constructor parameter dir does not exist: " + dir));
		}
		if (!dir->isDirectory())
		{
			throw std::runtime_error(StringHelper::wstring_to_string(L"FileDataBuffer constructor parameter dir is not a directory: " + dir));
		}
		path = dir->getPath() + L"/" + id;
		std::shared_ptr<File> subDir = std::make_shared<File>(path);
		subDir->mkdir();
		buffer = std::vector<std::shared_ptr<MappedByteBuffer>>(banks);
		accessFiles = std::vector<std::shared_ptr<RandomAccessFile>>(banks);
		files = std::vector<std::shared_ptr<File>>(banks);
		for (int i = 0; i < banks; i++)
		{
			std::shared_ptr<File> file = files[i] = std::make_shared<File>(path + L"/bank" + std::to_wstring(i) + L".dat");
			constexpr std::shared_ptr<RandomAccessFile> randomAccessFile = accessFiles[i] = std::make_shared<RandomAccessFile>(file, L"rw");
			buffer[i] = randomAccessFile->getChannel().map(FileChannel::MapMode::READ_WRITE, 0, getSize());
		}
	}

	int BigBufferedImage::FileDataBuffer::getElem(int bank, int i)
	{
		return buffer[bank]->get(i) & 0xff;
	}

	void BigBufferedImage::FileDataBuffer::setElem(int bank, int i, int val)
	{
		buffer[bank]->put(i, static_cast<signed char>(val));
	}

//JAVA TO C++ CONVERTER WARNING: There is no equivalent in C++ to finalizer methods:
	void BigBufferedImage::FileDataBuffer::finalize()
	{
		dispose();
	}

	void BigBufferedImage::FileDataBuffer::dispose()
	{
		(std::make_shared<ThreadAnonymousInnerClass>(shared_from_this()))->start();
	}

	BigBufferedImage::FileDataBuffer::ThreadAnonymousInnerClass::ThreadAnonymousInnerClass(std::shared_ptr<FileDataBuffer> outerInstance) : outerInstance(outerInstance)
	{
	}

	void BigBufferedImage::FileDataBuffer::ThreadAnonymousInnerClass::run()
	{
		outerInstance->disposeNow();
	}

	void BigBufferedImage::FileDataBuffer::disposeNow()
	{
		this->buffer = std::vector<std::shared_ptr<MappedByteBuffer>>();
		if (!accessFiles.empty())
		{
			for (auto file : accessFiles)
			{
				try
				{
					file->close();
				}
				catch (const IOException &e)
				{
					e->printStackTrace();
				}
			}
			accessFiles = std::vector<std::shared_ptr<RandomAccessFile>>();
		}
		if (!files.empty())
		{
			for (auto file : files)
			{
				file->delete();
			}
			files = std::vector<std::shared_ptr<File>>();
		}
		if (path != L"")
		{
			(std::make_shared<File>(path))->delete();
			path = L"";
		}
	}
}
