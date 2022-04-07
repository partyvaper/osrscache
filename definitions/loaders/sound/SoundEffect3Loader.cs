namespace OSRSCache.definitions.loaders.sound
{
	using SoundEffect2Definition = OSRSCache.definitions.sound.SoundEffect2Definition;
	using SoundEffect3Definition = OSRSCache.definitions.sound.SoundEffect3Definition;
	using InputStream = OSRSCache.io.InputStream;

	public class SoundEffect3Loader
	{
		private readonly SoundEffect2Loader se2Loader = new SoundEffect2Loader();

		public virtual SoundEffect3Definition load(InputStream @in, SoundEffect2Definition var2)
		{
			SoundEffect3Definition se = new SoundEffect3Definition();

			load(se, @in, var2);

			return se;
		}

		private void load(SoundEffect3Definition se, InputStream var1, SoundEffect2Definition var2)
		{
			int var3 = var1.readUnsignedByte();
			se.field1155[0] = var3 >> 4;
			se.field1155[1] = var3 & 15;
			if (var3 != 0)
			{
				se.field1156[0] = var1.readUnsignedShort();
				se.field1156[1] = var1.readUnsignedShort();
				int var4 = var1.readUnsignedByte();

				int var5;
				int var6;
				for (var5 = 0; var5 < 2; ++var5)
				{
					for (var6 = 0; var6 < se.field1155[var5]; ++var6)
					{
						se.field1154[var5][0][var6] = var1.readUnsignedShort();
						se.field1159[var5][0][var6] = var1.readUnsignedShort();
					}
				}

				for (var5 = 0; var5 < 2; ++var5)
				{
					for (var6 = 0; var6 < se.field1155[var5]; ++var6)
					{
						if ((var4 & 1 << var5 * 4 << var6) != 0)
						{
							se.field1154[var5][1][var6] = var1.readUnsignedShort();
							se.field1159[var5][1][var6] = var1.readUnsignedShort();
						}
						else
						{
							se.field1154[var5][1][var6] = se.field1154[var5][0][var6];
							se.field1159[var5][1][var6] = se.field1159[var5][0][var6];
						}
					}
				}

				if (var4 != 0 || se.field1156[1] != se.field1156[0])
				{
					se2Loader.method1144(var2, var1);
				}
			}
			else
			{
				int[] var7 = se.field1156;
				se.field1156[1] = 0;
				var7[0] = 0;
			}
		}
	}

}