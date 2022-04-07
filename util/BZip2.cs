using System;
using System.Diagnostics;
using System.IO;
using ICSharpCode.SharpZipLib.BZip2;

namespace OSRSCache.util
{
	public class BZip2
	{
		private static readonly byte[] BZIP_HEADER = new byte[] {(byte)'B', (byte)'Z', (byte)'h', (byte)'1'};

		public static byte[] compress(byte[] bytes)
		{
			Stream @is = new MemoryStream(bytes);
			MemoryStream bout = new MemoryStream();
			using (Stream os = new BZip2OutputStream(bout, 1))
			{
				// IOUtils.copy(@is, os);
				@is.CopyTo(os);
			}

			byte[] @out = bout.ToArray();

			Debug.Assert(BZIP_HEADER[0] == @out[0]);
			Debug.Assert(BZIP_HEADER[1] == @out[1]);
			Debug.Assert(BZIP_HEADER[2] == @out[2]);
			Debug.Assert(BZIP_HEADER[3] == @out[3]);

			return Arrays.CopyOfRange(@out, BZIP_HEADER.Length, @out.Length);
		}

		public static byte[] decompress(byte[] bytes, int len)
		{
			byte[] data = new byte[len + BZIP_HEADER.Length];

			// add header
			Array.Copy(BZIP_HEADER, 0, data, 0, BZIP_HEADER.Length);
			Array.Copy(bytes, 0, data, BZIP_HEADER.Length, len);

			MemoryStream os = new MemoryStream();

			using (Stream @is = new BZip2InputStream(new MemoryStream(data)))
			{
				// IOUtils.copy(@is, os);
				@is.CopyTo(os);
			}

			return os.ToArray();
		}
	}

}