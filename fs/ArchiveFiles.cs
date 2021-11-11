using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;

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
namespace OSRSCache.fs
{
	// using Preconditions = com.google.common.@base.Preconditions;
	using InputStream = OSRSCache.io.InputStream;
	using OutputStream = OSRSCache.io.OutputStream;


	public class ArchiveFiles
	{
		private readonly IList<FSFile> files = new List<FSFile>();
		private readonly IDictionary<int, FSFile> fileMap = new Dictionary<int, FSFile>();

		public override int GetHashCode()
		{
			int hash = 7;
			hash = 67 * hash + this.files.GetHashCode();
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
//ORIGINAL LINE: final ArchiveFiles other = (ArchiveFiles) obj;
			ArchiveFiles other = (ArchiveFiles) obj;
			if (!Object.Equals(this.files, other.files))
			{
				return false;
			}
			return true;
		}

		public virtual void addFile(FSFile file)
		{
			// Preconditions.checkArgument(file.FileId != -1);
			if (file.FileId == -1)
			{
				return;
			}
			if (fileMap.ContainsKey(file.FileId))
			{
				throw new System.InvalidOperationException("duplicate file ids");
			}

			files.Add(file);
			fileMap[file.FileId] = file;
		}

		public virtual IList<FSFile> Files
		{
			get
			{
				return new List<FSFile>(files);
			}
		}

		public virtual FSFile findFile(int fileId)
		{
			return fileMap[fileId];
		}

		public virtual void clear()
		{
			files.Clear();
			fileMap.Clear();
		}

		public virtual void loadContents(byte[] data)
		{
			Console.WriteLine("Loading contents of archive ({} files)", files.Count);

			Debug.Assert(this.Files.Count > 0);

			if (this.Files.Count == 1)
			{
				this.Files[0].Contents = data;
				return;
			}

			int filesCount = this.Files.Count;

			InputStream stream = new InputStream(data);
			stream.Offset = stream.Length - 1;
			int chunks = stream.readUnsignedByte();

			// -1 for chunks count + one int per file slot per chunk
			stream.Offset = stream.Length - 1 - chunks * filesCount * 4;
//JAVA TO C# CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: int[][] chunkSizes = new int[filesCount][chunks];
			int[][] chunkSizes = RectangularArrays.RectangularIntArray(filesCount, chunks);
			int[] filesSize = new int[filesCount];

			for (int chunk = 0; chunk < chunks; ++chunk)
			{
				int chunkSize = 0;

				for (int id = 0; id < filesCount; ++id)
				{
					int delta = stream.readInt();
					chunkSize += delta; // size of this chunk

					chunkSizes[id][chunk] = chunkSize; // store size of chunk

					filesSize[id] += chunkSize; // add chunk size to file size
				}
			}

			byte[][] fileContents = new byte[filesCount][];
			int[] fileOffsets = new int[filesCount];

			for (int i = 0; i < filesCount; ++i)
			{
				fileContents[i] = new byte[filesSize[i]];
			}

			// the file data is at the beginning of the stream
			stream.Offset = 0;

			for (int chunk = 0; chunk < chunks; ++chunk)
			{
				for (int id = 0; id < filesCount; ++id)
				{
					int chunkSize = chunkSizes[id][chunk];

					stream.readBytes(fileContents[id], fileOffsets[id], chunkSize);

					fileOffsets[id] += chunkSize;
				}
			}

			for (int i = 0; i < filesCount; ++i)
			{
				FSFile f = this.Files[i];
				f.Contents = fileContents[i];
			}
		}

		public virtual byte[] saveContents()
		{
			OutputStream stream = new OutputStream();

			int filesCount = this.Files.Count;

			if (filesCount == 1)
			{
				FSFile file = this.Files[0];
				stream.writeBytes(file.Contents);
			}
			else
			{
				foreach (FSFile file in this.Files)
				{
					byte[] contents = file.Contents;
					stream.writeBytes(contents);
				}

				int offset = 0;

				foreach (FSFile file in this.Files)
				{
					int chunkSize = file.Size;

					int sz = chunkSize - offset;
					offset = chunkSize;
					stream.writeInt(sz);
				}

				stream.writeByte(1); // chunks
			}

			byte[] fileData = stream.flip();

			Console.WriteLine("Saved contents of archive ({} files), {} bytes", files.Count, fileData.Length);
			return fileData;
		}
	}

}