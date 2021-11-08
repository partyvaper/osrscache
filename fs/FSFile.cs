using System.Linq;

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

namespace net.runelite.cache.fs
{

	public class FSFile
	{
		private readonly int fileId;
		private int nameHash;
		private sbyte[] contents;

		public FSFile(int fileId)
		{
			this.fileId = fileId;
		}

		public override int GetHashCode()
		{
			int hash = 7;
			hash = 97 * hash + this.fileId;
			hash = 97 * hash + this.nameHash;
			hash = 97 * hash + Arrays.hashCode(this.contents);
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
//ORIGINAL LINE: final FSFile other = (FSFile) obj;
			FSFile other = (FSFile) obj;
			if (this.fileId != other.fileId)
			{
				return false;
			}
			if (this.nameHash != other.nameHash)
			{
				return false;
			}
			if (!this.contents.SequenceEqual(other.contents))
			{
				return false;
			}
			return true;
		}

		public virtual int FileId
		{
			get
			{
				return fileId;
			}
		}

		public virtual int NameHash
		{
			get
			{
				return nameHash;
			}
			set
			{
				this.nameHash = value;
			}
		}


		public virtual sbyte[] Contents
		{
			get
			{
				return contents;
			}
			set
			{
				this.contents = value;
			}
		}


		public virtual int Size
		{
			get
			{
				return contents.Length;
			}
		}
	}

}