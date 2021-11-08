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

namespace net.runelite.cache.fs.jagex
{

	public class IndexEntry
	{
		private readonly IndexFile indexFile;
		private readonly int id, sector, length;

		public IndexEntry(IndexFile indexFile, int id, int sector, int length)
		{
			this.indexFile = indexFile;
			this.id = id;
			this.sector = sector;
			this.length = length;
		}

		public virtual IndexFile IndexFile
		{
			get
			{
				return indexFile;
			}
		}

		public virtual int Id
		{
			get
			{
				return id;
			}
		}

		public virtual int Sector
		{
			get
			{
				return sector;
			}
		}

		public virtual int Length
		{
			get
			{
				return length;
			}
		}

		public override int GetHashCode()
		{
			int hash = 7;
			hash = 19 * hash + Objects.hashCode(this.indexFile);
			hash = 19 * hash + this.id;
			hash = 19 * hash + this.sector;
			hash = 19 * hash + this.length;
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
//ORIGINAL LINE: final IndexEntry other = (IndexEntry) obj;
			IndexEntry other = (IndexEntry) obj;
			if (!Objects.equals(this.indexFile, other.indexFile))
			{
				return false;
			}
			if (this.id != other.id)
			{
				return false;
			}
			if (this.sector != other.sector)
			{
				return false;
			}
			if (this.length != other.length)
			{
				return false;
			}
			return true;
		}
	}

}