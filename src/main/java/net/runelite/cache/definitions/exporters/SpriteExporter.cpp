#include "SpriteExporter.h"

namespace net::runelite::cache::definitions::exporters
{
	using BufferedImage = java::awt::image::BufferedImage;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using ImageIO = javax::imageio::ImageIO;
	using SpriteDefinition = net::runelite::cache::definitions::SpriteDefinition;

	SpriteExporter::SpriteExporter(std::shared_ptr<SpriteDefinition> sprite) : sprite(sprite)
	{
	}

	std::shared_ptr<BufferedImage> SpriteExporter::export_Keyword()
	{
		std::shared_ptr<BufferedImage> bi = std::make_shared<BufferedImage>(sprite->getWidth(), sprite->getHeight(), BufferedImage::TYPE_INT_ARGB);
		bi->setRGB(0, 0, sprite->getWidth(), sprite->getHeight(), sprite->getPixels(), 0, sprite->getWidth());
		return bi;
	}

	void SpriteExporter::exportTo(std::shared_ptr<File> file)
	{
		std::shared_ptr<BufferedImage> image = export_Keyword();
		ImageIO::write(image, L"png", file);
	}
}
