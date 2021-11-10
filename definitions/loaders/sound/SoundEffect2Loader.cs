namespace OSRSCache.definitions.loaders.sound
{
	using SoundEffect2Definition = OSRSCache.definitions.sound.SoundEffect2Definition;
	using InputStream = OSRSCache.io.InputStream;

	public class SoundEffect2Loader
	{
		public virtual SoundEffect2Definition load(InputStream @in)
		{
			SoundEffect2Definition se = new SoundEffect2Definition();

			load(se, @in);

			return se;
		}

		private void load(SoundEffect2Definition se, InputStream var1)
		{
			se.field1087 = var1.readUnsignedByte();
			se.field1088 = var1.readInt();
			se.field1089 = var1.readInt();
			this.method1144(se, var1);
		}

		internal void method1144(SoundEffect2Definition se, InputStream var1)
		{
			se.field1092 = var1.readUnsignedByte();
			se.field1086 = new int[se.field1092];
			se.field1090 = new int[se.field1092];

			for (int var2 = 0; var2 < se.field1092; ++var2)
			{
				se.field1086[var2] = var1.readUnsignedShort();
				se.field1090[var2] = var1.readUnsignedShort();
			}

		}
	}

}