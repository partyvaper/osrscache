using System.Diagnostics;
using System.IO;
using System.Text;

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
namespace OSRSCache.io
{

	public class InputStream : Stream
	{
		private static readonly char[] CHARACTERS = new char[] {'\u20ac', '\u0000', '\u201a', '\u0192', '\u201e', '\u2026', '\u2020', '\u2021', '\u02c6', '\u2030', '\u0160', '\u2039', '\u0152', '\u0000', '\u017d', '\u0000', '\u0000', '\u2018', '\u2019', '\u201c', '\u201d', '\u2022', '\u2013', '\u2014', '\u02dc', '\u2122', '\u0161', '\u203a', '\u0153', '\u0000', '\u017e', '\u0178'};

		private readonly ByteBuffer buffer;

		public InputStream(sbyte[] buffer)
		{
			this.buffer = ByteBuffer.wrap(buffer);
		}

		public virtual sbyte[] Array
		{
			get
			{
				Debug.Assert(buffer.hasArray());
				return buffer.array();
			}
		}

		public override string ToString()
		{
			return "InputStream{" + "buffer=" + buffer + '}';
		}

		public virtual int read24BitInt()
		{
			return (this.readUnsignedByte() << 16) + (this.readUnsignedByte() << 8) + this.readUnsignedByte();
		}

		public virtual void skip(int length)
		{
			int pos = buffer.position();
			pos += length;
			buffer.position(pos);
		}

		public virtual int Offset
		{
			set
			{
				buffer.position(value);
			}
			get
			{
				return buffer.position();
			}
		}


		public virtual int Length
		{
			get
			{
				return buffer.limit();
			}
		}

		public virtual int remaining()
		{
			return buffer.remaining();
		}

		public virtual sbyte readByte()
		{
			return buffer.get();
		}

		public virtual void readBytes(sbyte[] buffer, int off, int len)
		{
			this.buffer.get(buffer, off, len);
		}

		public virtual void readBytes(sbyte[] buffer)
		{
			this.buffer.get(buffer);
		}

		public virtual int readUnsignedByte()
		{
			return this.readByte() & 0xFF;
		}

		public virtual int readUnsignedShort()
		{
			return buffer.getShort() & 0xFFFF;
		}

		public virtual short readShort()
		{
			return buffer.getShort();
		}

		public virtual int readInt()
		{
			return buffer.getInt();
		}

		public virtual sbyte peek()
		{
			return buffer.get(buffer.position());
		}

		public virtual int readBigSmart()
		{
			return peek() >= 0 ? (this.readUnsignedShort() & 0xFFFF) : (this.readInt() & int.MaxValue);
		}

		public virtual int readBigSmart2()
		{
			if (peek() < 0)
			{
				return readInt() & int.MaxValue; // and off sign bit
			}
			int value = readUnsignedShort();
			return value == 32767 ? -1 : value;
		}

		public virtual int readShortSmart()
		{
			int peek = this.peek() & 0xFF;
			return peek < 128 ? this.readUnsignedByte() - 64 : this.readUnsignedShort() - 0xc000;
		}

		public virtual int readUnsignedShortSmart()
		{
			int peek = this.peek() & 0xFF;
			return peek < 128 ? this.readUnsignedByte() : this.readUnsignedShort() - 0x8000;
		}

		public virtual int readUnsignedIntSmartShortCompat()
		{
			int var1 = 0;

			int var2;
			for (var2 = this.readUnsignedShortSmart(); var2 == 32767; var2 = this.readUnsignedShortSmart())
			{
				var1 += 32767;
			}

			var1 += var2;
			return var1;
		}

		public virtual string readString()
		{
			StringBuilder sb = new StringBuilder();

			for (; ;)
			{
				int ch = this.readUnsignedByte();

				if (ch == 0)
				{
					break;
				}

				if (ch >= 128 && ch < 160)
				{
					char var7 = CHARACTERS[ch - 128];
					if ((char)0 == var7)
					{
						var7 = '?';
					}

					ch = var7;
				}

				sb.Append((char) ch);
			}
			return sb.ToString();
		}

		public virtual string readString2()
		{
			if (this.readByte() != 0)
			{
				throw new System.InvalidOperationException("Invalid jstr2");
			}
			else
			{
				return readString();
			}
		}

		public virtual string readStringOrNull()
		{
			if (this.peek() != 0)
			{
				return readString();
			}
			else
			{
				this.readByte(); // discard
				return null;
			}
		}

		public virtual int readVarInt()
		{
			sbyte var1 = this.readByte();

			int var2;
			for (var2 = 0; var1 < 0; var1 = this.readByte())
			{
				var2 = (var2 | var1 & 127) << 7;
			}

			return var2 | var1;
		}

		public virtual sbyte[] Remaining
		{
			get
			{
				sbyte[] b = new sbyte[buffer.remaining()];
				buffer.get(b);
				return b;
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public int read() throws java.io.IOException
		public override int read()
		{
			return this.readUnsignedByte();
		}
	}

}