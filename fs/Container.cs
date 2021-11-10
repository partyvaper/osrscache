using System;
using System.Diagnostics;

namespace OSRSCache.fs
{
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static com.google.common.primitives.Bytes.concat;
	using Ints = com.google.common.primitives.Ints;
	using CompressionType = OSRSCache.fs.jagex.CompressionType;
	using InputStream = OSRSCache.io.InputStream;
	using OutputStream = OSRSCache.io.OutputStream;
	using BZip2 = OSRSCache.util.BZip2;
	using Crc32 = OSRSCache.util.Crc32;
	using GZip = OSRSCache.util.GZip;
	using Xtea = OSRSCache.util.Xtea;


	public class Container
	{
		public sbyte[] data;
		public int compression; // compression
		public int revision;
		public int crc; // crc of compressed data

		public Container(int compression, int revision)
		{
			this.compression = compression;
			this.revision = revision;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void compress(byte[] data, int[] keys) throws java.io.IOException
		public virtual void compress(sbyte[] data, int[] keys)
		{
			OutputStream stream = new OutputStream();

			sbyte[] compressedData;
			int length;
			switch (compression)
			{
				case CompressionType.NONE:
					compressedData = data;
					length = compressedData.Length;
					break;
				case CompressionType.BZ2:
					compressedData = concat(Ints.toByteArray(data.Length), BZip2.compress(data));
					length = compressedData.Length - 4;
					break;
				case CompressionType.GZ:
					compressedData = concat(Ints.toByteArray(data.Length), GZip.compress(data));
					length = compressedData.Length - 4;
					break;
				default:
					throw new Exception("Unknown compression type");
			}

			compressedData = encrypt(compressedData, compressedData.Length, keys);

			stream.writeByte(compression);
			stream.writeInt(length);

			stream.writeBytes(compressedData);
			if (revision != -1)
			{
				stream.writeShort(revision);
			}

			this.data = stream.flip();
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public static Container decompress(byte[] b, int[] keys) throws java.io.IOException
		public static Container decompress(sbyte[] b, int[] keys)
		{
			InputStream stream = new InputStream(b);

			int compression = stream.readUnsignedByte();
			int compressedLength = stream.readInt();
			if (compressedLength < 0 || compressedLength > 1000000)
			{
				throw new Exception("Invalid data");
			}

			Crc32 crc32 = new Crc32();
			crc32.update(b, 0, 5); // compression + length

			sbyte[] data;
			int revision = -1;
			switch (compression)
			{
				case CompressionType.NONE:
				{
					sbyte[] encryptedData = new sbyte[compressedLength];
					stream.readBytes(encryptedData, 0, compressedLength);

					crc32.update(encryptedData, 0, compressedLength);
					sbyte[] decryptedData = decrypt(encryptedData, encryptedData.Length, keys);

					if (stream.remaining() >= 2)
					{
						revision = stream.readUnsignedShort();
						Debug.Assert(revision != -1);
					}

					data = decryptedData;

					break;
				}
				case CompressionType.BZ2:
				{
					sbyte[] encryptedData = new sbyte[compressedLength + 4];
					stream.readBytes(encryptedData);

					crc32.update(encryptedData, 0, encryptedData.Length);
					sbyte[] decryptedData = decrypt(encryptedData, encryptedData.Length, keys);

					if (stream.remaining() >= 2)
					{
						revision = stream.readUnsignedShort();
						Debug.Assert(revision != -1);
					}

					stream = new InputStream(decryptedData);

					int decompressedLength = stream.readInt();
					data = BZip2.decompress(stream.Remaining, compressedLength);

					if (data == null)
					{
						return null;
					}

					Debug.Assert(data.Length == decompressedLength);

					break;
				}
				case CompressionType.GZ:
				{
					sbyte[] encryptedData = new sbyte[compressedLength + 4];
					stream.readBytes(encryptedData);

					crc32.update(encryptedData, 0, encryptedData.Length);
					sbyte[] decryptedData = decrypt(encryptedData, encryptedData.Length, keys);

					if (stream.remaining() >= 2)
					{
						revision = stream.readUnsignedShort();
						Debug.Assert(revision != -1);
					}

					stream = new InputStream(decryptedData);

					int decompressedLength = stream.readInt();
					data = GZip.decompress(stream.Remaining, compressedLength);

					if (data == null)
					{
						return null;
					}

					Debug.Assert(data.Length == decompressedLength);

					break;
				}
				default:
					throw new Exception("Unknown decompression type");
			}

			Container container = new Container(compression, revision);
			container.data = data;
			container.crc = crc32.Hash;
			return container;
		}

		private static sbyte[] decrypt(sbyte[] data, int length, int[] keys)
		{
			if (keys == null)
			{
				return data;
			}

			Xtea xtea = new Xtea(keys);
			return xtea.decrypt(data, length);
		}

		private static sbyte[] encrypt(sbyte[] data, int length, int[] keys)
		{
			if (keys == null)
			{
				return data;
			}

			Xtea xtea = new Xtea(keys);
			return xtea.encrypt(data, length);
		}
	}

}