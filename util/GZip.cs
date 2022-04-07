using System.IO;
using ICSharpCode.SharpZipLib.GZip;

namespace OSRSCache.util
{
	public class GZip
	{
		public static byte[] compress(byte[] bytes)
		{
			Stream @is = new MemoryStream(bytes);
			MemoryStream bout = new MemoryStream();

			using (Stream os = new GZipInputStream(bout))
			{
				// IOUtils.copy(@is, os);
				@is.CopyTo(os);
			}

			return bout.ToArray();
		}

		public static byte[] decompress(byte[] bytes, int len)
		{
			MemoryStream os = new MemoryStream();

			using (Stream @is = new GZipInputStream(new MemoryStream(bytes, 0, len)))
			{
				// IOUtils.copy(@is, os);
				@is.CopyTo(os);
			}

			return os.ToArray();
		}
	}

}