namespace OSRSCache.definitions.exporters
{
	using SpriteDefinition = OSRSCache.definitions.SpriteDefinition;

	public class SpriteExporter
	{
		private readonly SpriteDefinition sprite;

		public SpriteExporter(SpriteDefinition sprite)
		{
			this.sprite = sprite;
		}

		// public virtual BufferedImage export()
		// {
		// 	BufferedImage bi = new BufferedImage(sprite.width, sprite.height, BufferedImage.TYPE_INT_ARGB);
		// 	bi.setRGB(0, 0, sprite.width, sprite.height, sprite.pixels, 0, sprite.width);
		// 	return bi;
		// }

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void exportTo(java.io.File file) throws java.io.IOException
		// public virtual void exportTo(string file)
		// {
		// 	BufferedImage image = export();
		// 	ImageIO.write(image, "png", file);
		// }
	}

}