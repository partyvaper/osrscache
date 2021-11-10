using System;

namespace OSRSCache.definitions
{
	
	public class OverlayDefinition
	{
		public int id; // all was private now is public
		public int rgbColor = 0;
		public int texture = -1;
		public int secondaryRgbColor = -1;
		public bool hideUnderlay = true;

		[NonSerialized]
		public int hue;
		[NonSerialized]
		public int saturation;
		[NonSerialized]
		public int lightness;

		[NonSerialized]
		public int otherHue;
		[NonSerialized]
		public int otherSaturation;
		[NonSerialized]
		public int otherLightness;

		public virtual void calculateHsl()
		{
			if (secondaryRgbColor != -1)
			{
				calculateHsl(secondaryRgbColor);
				otherHue = hue;
				otherSaturation = saturation;
				otherLightness = lightness;
			}

			calculateHsl(rgbColor);
		}

		private void calculateHsl(int var1)
		{
			double var2 = (double)(var1 >> 16 & 255) / 256.0D;
			double var4 = (double)(var1 >> 8 & 255) / 256.0D;
			double var6 = (double)(var1 & 255) / 256.0D;
			double var8 = var2;
			if (var4 < var2)
			{
				var8 = var4;
			}

			if (var6 < var8)
			{
				var8 = var6;
			}

			double var10 = var2;
			if (var4 > var2)
			{
				var10 = var4;
			}

			if (var6 > var10)
			{
				var10 = var6;
			}

			double var12 = 0.0D;
			double var14 = 0.0D;
			double var16 = (var8 + var10) / 2.0D;
			if (var10 != var8)
			{
				if (var16 < 0.5D)
				{
					var14 = (var10 - var8) / (var10 + var8);
				}

				if (var16 >= 0.5D)
				{
					var14 = (var10 - var8) / (2.0D - var10 - var8);
				}

				if (var2 == var10)
				{
					var12 = (var4 - var6) / (var10 - var8);
				}
				else if (var4 == var10)
				{
					var12 = 2.0D + (var6 - var2) / (var10 - var8);
				}
				else if (var10 == var6)
				{
					var12 = 4.0D + (var2 - var4) / (var10 - var8);
				}
			}

			var12 /= 6.0D;
			this.hue = (int)(256.0D * var12);
			this.saturation = (int)(var14 * 256.0D);
			this.lightness = (int)(var16 * 256.0D);
			if (this.saturation < 0)
			{
				this.saturation = 0;
			}
			else if (this.saturation > 255)
			{
				this.saturation = 255;
			}

			if (this.lightness < 0)
			{
				this.lightness = 0;
			}
			else if (this.lightness > 255)
			{
				this.lightness = 255;
			}

		}
	}

}