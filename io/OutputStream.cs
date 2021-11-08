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
namespace net.runelite.cache.io
{
	using Preconditions = com.google.common.@base.Preconditions;

	public sealed class OutputStream : Stream
	{
		private ByteBuffer buffer;

		public OutputStream(int capacity)
		{
			buffer = ByteBuffer.allocate(capacity);
		}

		public OutputStream() : this(16)
		{
		}

		public sbyte[] Array
		{
			get
			{
				Debug.Assert(buffer.hasArray());
				return buffer.array();
			}
		}

		private void ensureRemaining(int remaining)
		{
			while (remaining > buffer.remaining())
			{
				int newCapacity = buffer.capacity() * 2;

				ByteBuffer old = buffer;
				old.flip();

				buffer = ByteBuffer.allocate(newCapacity);

				buffer.put(old);
			}
		}

		public void skip(int length)
		{
			int pos = buffer.position();
			pos += length;
			buffer.position(pos);
		}

		public int Offset
		{
			get
			{
				return buffer.position();
			}
			set
			{
				buffer.position(value);
			}
		}


		public void writeBytes(sbyte[] b)
		{
			writeBytes(b, 0, b.Length);
		}

		public void writeBytes(sbyte[] b, int offset, int length)
		{
			ensureRemaining(length);
			buffer.put(b, offset, length);
		}

		public void writeByte(int i)
		{
			ensureRemaining(1);
			buffer.put((sbyte) i);
		}

		public void writeBigSmart(int value)
		{
			Preconditions.checkArgument(value >= 0);
			if (value >= 32768)
			{
				ensureRemaining(4);
				this.writeInt((1 << 31) | value);
			}
			else
			{
				ensureRemaining(2);
				this.writeShort(value);
			}
		}

		public void writeShort(int i)
		{
			ensureRemaining(2);
			buffer.putShort((short) i);
		}

		public void writeShortSmart(int value)
		{
			Preconditions.checkArgument(value >= 0);
			if (value < 128)
			{
				writeByte(value);
			}
			else
			{
				writeShort(0x8000 | value);
			}
		}

		public void write24BitInt(int i)
		{
			ensureRemaining(3);
			buffer.put((sbyte)((int)((uint)i >> 16)));
			buffer.put((sbyte)((int)((uint)i >> 8)));
			buffer.put(unchecked((sbyte)(i & 0xFF)));
		}

		public void writeInt(int i)
		{
			ensureRemaining(4);
			buffer.putInt(i);
		}

		public void writeVarInt(int var1)
		{
			if ((var1 & -128) != 0)
			{
				if ((var1 & -16384) != 0)
				{
					if ((var1 & -2097152) != 0)
					{
						if ((var1 & -268435456) != 0)
						{
							this.writeByte((int)((uint)var1 >> 28) | 128);
						}

						this.writeByte((int)((uint)var1 >> 21) | 128);
					}

					this.writeByte((int)((uint)var1 >> 14) | 128);
				}

				this.writeByte((int)((uint)var1 >> 7) | 128);
			}

			this.writeByte(var1 & 127);
		}

		public void writeLengthFromMark(int var1)
		{
			this.Array[this.Offset - var1 - 4] = (sbyte)(var1 >> 24);
			this.Array[this.Offset - var1 - 3] = (sbyte)(var1 >> 16);
			this.Array[this.Offset - var1 - 2] = (sbyte)(var1 >> 8);
			this.Array[this.Offset - var1 - 1] = (sbyte) var1;
		}

		public void writeString(string str)
		{
			writeBytes(str.GetBytes(StandardCharsets.ISO_8859_1));
			writeByte(0);
		}

		public sbyte[] flip()
		{
			buffer.flip();
			sbyte[] b = new sbyte[buffer.limit()];
			buffer.get(b);
			return b;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void write(int b) throws java.io.IOException
		public override void write(int b)
		{
			buffer.put((sbyte) b);
		}

	}

}