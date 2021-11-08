using System;
using System.Diagnostics;
using System.IO;

/*
 * Copyright (c) 2016-2017, Adam <Adam@sigterm.info>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
namespace net.runelite.cache.util
{
	using BZip2CompressorInputStream = org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
	using BZip2CompressorOutputStream = org.apache.commons.compress.compressors.bzip2.BZip2CompressorOutputStream;
	using IOUtils = org.apache.commons.compress.utils.IOUtils;
	using Logger = org.slf4j.Logger;
	using LoggerFactory = org.slf4j.LoggerFactory;

	public class BZip2
	{
		private static readonly Logger logger = LoggerFactory.getLogger(typeof(BZip2));

		private static readonly sbyte[] BZIP_HEADER = new sbyte[] {(sbyte)'B', (sbyte)'Z', (sbyte)'h', (sbyte)'1'};

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public static byte[] compress(byte[] bytes) throws java.io.IOException
		public static sbyte[] compress(sbyte[] bytes)
		{
			Stream @is = new MemoryStream(bytes);
			MemoryStream bout = new MemoryStream();
			using (Stream os = new BZip2CompressorOutputStream(bout, 1))
			{
				IOUtils.copy(@is, os);
			}

			sbyte[] @out = bout.toByteArray();

			Debug.Assert(BZIP_HEADER[0] == @out[0]);
			Debug.Assert(BZIP_HEADER[1] == @out[1]);
			Debug.Assert(BZIP_HEADER[2] == @out[2]);
			Debug.Assert(BZIP_HEADER[3] == @out[3]);

			return Arrays.CopyOfRange(@out, BZIP_HEADER.Length, @out.Length); // remove header..
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public static byte[] decompress(byte[] bytes, int len) throws java.io.IOException
		public static sbyte[] decompress(sbyte[] bytes, int len)
		{
			sbyte[] data = new sbyte[len + BZIP_HEADER.Length];

			// add header
			Array.Copy(BZIP_HEADER, 0, data, 0, BZIP_HEADER.Length);
			Array.Copy(bytes, 0, data, BZIP_HEADER.Length, len);

			MemoryStream os = new MemoryStream();

			using (Stream @is = new BZip2CompressorInputStream(new MemoryStream(data)))
			{
				IOUtils.copy(@is, os);
			}

			return os.toByteArray();
		}
	}

}