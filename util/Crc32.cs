using System;
using Force.Crc32;

namespace OSRSCache.util
{

	public class Crc32
	{
		private readonly Crc32Algorithm crc32 = new Crc32Algorithm();
		private byte[] hash;

		public virtual void update(sbyte[] sdata, int offset, int length)
		{
			// sbyte (-127,127) to byte (0,255)
			byte[] data = (byte[]) (Array)sdata;
			hash = crc32.ComputeHash(data, offset, length);
		}

		public virtual int Hash
		{
			get
			{
				// return Convert.ToInt32(hash);
				return Convert.ToInt32(crc32.Hash);
			}
		}
	}

}