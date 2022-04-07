namespace OSRSCache.definitions.loaders.sound
{
	using SoundEffectDefinition = OSRSCache.definitions.sound.SoundEffectDefinition;
	using SoundEffect1Definition = OSRSCache.definitions.sound.SoundEffect1Definition;
	using InputStream = OSRSCache.io.InputStream;

	public class SoundEffectLoader
	{
		public virtual SoundEffectDefinition load(byte[] b)
		{
			SoundEffectDefinition se = new SoundEffectDefinition();
			InputStream @in = new InputStream(b);

			load(se, @in);

			return se;
		}

		private void load(SoundEffectDefinition se, InputStream var1)
		{
			for (int var2 = 0; var2 < 10; ++var2)
			{
				int var3 = var1.readUnsignedByte();
				if (var3 != 0)
				{
					var1.Offset = var1.Offset - 1;

					SoundEffect1Loader se1Loader = new SoundEffect1Loader();
					SoundEffect1Definition se1 = se1Loader.load(var1);

					se.field1008[var2] = se1;
				}
			}

			se.field1006 = var1.readUnsignedShort();
			se.field1009 = var1.readUnsignedShort();
		}
	}

}