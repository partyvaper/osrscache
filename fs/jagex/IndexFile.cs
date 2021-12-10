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

using System;

namespace OSRSCache.fs.jagex
{


	public class IndexFile : System.IDisposable
	{
		private const int INDEX_ENTRY_LEN = 6;

		private readonly int indexFileId;
		private readonly string file;
		private readonly RandomAccessFile idx;
		private readonly byte[] buffer = new byte[INDEX_ENTRY_LEN];

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public IndexFile(int indexFileId, java.io.File file) throws java.io.FileNotFoundException
		public IndexFile(int indexFileId, string file)
		{
			this.indexFileId = indexFileId;
			this.file = file;
			this.idx = new RandomAccessFile(file, "rw");
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void close() throws java.io.IOException
		public virtual void Dispose()
		{
			idx.close();
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void clear() throws java.io.IOException
		public virtual void clear()
		{
			idx.setLength(0L);
		}

		public override int GetHashCode()
		{
			int hash = 3;
			hash = 41 * hash + this.file.GetHashCode();
			return hash;
		}

		public override bool Equals(object obj)
		{
			if (obj == null)
			{
				return false;
			}
			if (this.GetType() != obj.GetType())
			{
				return false;
			}
//JAVA TO C# CONVERTER WARNING: The original Java variable was marked 'final':
//ORIGINAL LINE: final IndexFile other = (IndexFile) obj;
			IndexFile other = (IndexFile) obj;
			if (!Object.Equals(this.file, other.file))
			{
				return false;
			}
			return true;
		}

		public virtual int IndexFileId
		{
			get
			{
				return indexFileId;
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public synchronized void write(IndexEntry entry) throws java.io.IOException
		public virtual void write(IndexEntry entry)
		{
			lock (this)
			{
				idx.seek(entry.Id * INDEX_ENTRY_LEN);
        
				buffer[0] = (byte)(entry.Length >> 16);
				buffer[1] = (byte)(entry.Length >> 8);
				buffer[2] = (byte) entry.Length;
        
				buffer[3] = (byte)(entry.Sector >> 16);
				buffer[4] = (byte)(entry.Sector >> 8);
				buffer[5] = (byte) entry.Sector;
        
				idx.write(buffer);
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public synchronized IndexEntry read(int id) throws java.io.IOException
		public virtual IndexEntry read(int id)
		{
			lock (this)
			{
				idx.seek(id * INDEX_ENTRY_LEN);
				int i = idx.read(buffer);
				if (i != INDEX_ENTRY_LEN)
				{
					Console.WriteLine("short read for id {0} on index {1}: {2}", id, indexFileId, i);
					return null;
				}
        
				int length = ((buffer[0] & 0xFF) << 16) | ((buffer[1] & 0xFF) << 8) | (buffer[2] & 0xFF);
				int sector = ((buffer[3] & 0xFF) << 16) | ((buffer[4] & 0xFF) << 8) | (buffer[5] & 0xFF);
        
				if (length <= 0 || sector <= 0)
				{
					Console.WriteLine("invalid length or sector {0}/{1}", length, sector);
					return null;
				}
        
				return new IndexEntry(this, id, sector, length);
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public synchronized int getIndexCount() throws java.io.IOException
		public virtual int IndexCount
		{
			get
			{
				lock (this)
				{
					return (int)(idx.length() / INDEX_ENTRY_LEN);
				}
			}
		}
	}

}