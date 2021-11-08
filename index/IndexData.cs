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
namespace net.runelite.cache.index
{
	using InputStream = net.runelite.cache.io.InputStream;
	using OutputStream = net.runelite.cache.io.OutputStream;

	public class IndexData
	{
		private int protocol;
		private int revision;
		private bool named;
		private ArchiveData[] archives;

		public virtual void load(sbyte[] data)
		{
			InputStream stream = new InputStream(data);
			protocol = stream.readUnsignedByte();
			if (protocol < 5 || protocol > 7)
			{
				throw new System.ArgumentException("Unsupported protocol");
			}

			if (protocol >= 6)
			{
				this.revision = stream.readInt();
			}

			int hash = stream.readUnsignedByte();
			named = (1 & hash) != 0;
			if ((hash & ~1) != 0)
			{
				throw new System.ArgumentException("Unknown flags");
			}
			Debug.Assert((hash & ~3) == 0);
			int validArchivesCount = protocol >= 7 ? stream.readBigSmart() : stream.readUnsignedShort();
			int lastArchiveId = 0;

			archives = new ArchiveData[validArchivesCount];

			for (int index = 0; index < validArchivesCount; ++index)
			{
				int archive = lastArchiveId += protocol >= 7 ? stream.readBigSmart() : stream.readUnsignedShort();

				ArchiveData ad = new ArchiveData();
				ad.id = archive;
				archives[index] = ad;
			}

			if (named)
			{
				for (int index = 0; index < validArchivesCount; ++index)
				{
					int nameHash = stream.readInt();
					ArchiveData ad = archives[index];
					ad.nameHash = nameHash;
				}
			}

			for (int index = 0; index < validArchivesCount; ++index)
			{
				int crc = stream.readInt();

				ArchiveData ad = archives[index];
				ad.crc = crc;
			}

			for (int index = 0; index < validArchivesCount; ++index)
			{
				int revision = stream.readInt();

				ArchiveData ad = archives[index];
				ad.revision = revision;
			}

			int[] numberOfFiles = new int[validArchivesCount];
			for (int index = 0; index < validArchivesCount; ++index)
			{
				int num = protocol >= 7 ? stream.readBigSmart() : stream.readUnsignedShort();
				numberOfFiles[index] = num;
			}

			for (int index = 0; index < validArchivesCount; ++index)
			{
				ArchiveData ad = archives[index];
				int num = numberOfFiles[index];

				ad.files = new FileData[num];

				int last = 0;
				for (int i = 0; i < num; ++i)
				{
					int fileId = last += protocol >= 7 ? stream.readBigSmart() : stream.readUnsignedShort();

					FileData fd = ad.files[i] = new FileData();
					fd.id = fileId;
				}
			}

			if (named)
			{
				for (int index = 0; index < validArchivesCount; ++index)
				{
					ArchiveData ad = archives[index];
					int num = numberOfFiles[index];

					for (int i = 0; i < num; ++i)
					{
						FileData fd = ad.files[i];
						int name = stream.readInt();
						fd.nameHash = name;
					}
				}
			}
		}

		public virtual sbyte[] writeIndexData()
		{
			OutputStream stream = new OutputStream();
			stream.writeByte(protocol);
			if (protocol >= 6)
			{
				stream.writeInt(this.revision);
			}

			stream.writeByte(named ? 1 : 0);
			if (protocol >= 7)
			{
				stream.writeBigSmart(this.archives.Length);
			}
			else
			{
				stream.writeShort(this.archives.Length);
			}

			for (int i = 0; i < this.archives.Length; ++i)
			{
				ArchiveData a = this.archives[i];
				int archive = a.Id;

				if (i != 0)
				{
					ArchiveData prev = this.archives[i - 1];
					archive -= prev.Id;
				}

				if (protocol >= 7)
				{
					stream.writeBigSmart(archive);
				}
				else
				{
					stream.writeShort(archive);
				}
			}

			if (named)
			{
				for (int i = 0; i < this.archives.Length; ++i)
				{
					ArchiveData a = this.archives[i];
					stream.writeInt(a.NameHash);
				}
			}

			for (int i = 0; i < this.archives.Length; ++i)
			{
				ArchiveData a = this.archives[i];
				stream.writeInt(a.Crc);
			}

			for (int i = 0; i < this.archives.Length; ++i)
			{
				ArchiveData a = this.archives[i];
				stream.writeInt(a.Revision);
			}

			for (int i = 0; i < this.archives.Length; ++i)
			{
				ArchiveData a = this.archives[i];

				int len = a.Files.Length;

				if (protocol >= 7)
				{
					stream.writeBigSmart(len);
				}
				else
				{
					stream.writeShort(len);
				}
			}

			for (int i = 0; i < this.archives.Length; ++i)
			{
				ArchiveData a = this.archives[i];

				for (int j = 0; j < a.Files.Length; ++j)
				{
					FileData file = a.Files[j];
					int offset = file.Id;

					if (j != 0)
					{
						FileData prev = a.Files[j - 1];
						offset -= prev.Id;
					}

					if (protocol >= 7)
					{
						stream.writeBigSmart(offset);
					}
					else
					{
						stream.writeShort(offset);
					}
				}
			}

			if (named)
			{
				for (int i = 0; i < this.archives.Length; ++i)
				{
					ArchiveData a = this.archives[i];

					for (int j = 0; j < a.Files.Length; ++j)
					{
						FileData file = a.Files[j];
						stream.writeInt(file.NameHash);
					}
				}
			}

			return stream.flip();
		}

		public virtual int Protocol
		{
			get
			{
				return protocol;
			}
			set
			{
				this.protocol = value;
			}
		}


		public virtual int Revision
		{
			get
			{
				return revision;
			}
			set
			{
				this.revision = value;
			}
		}


		public virtual bool Named
		{
			get
			{
				return named;
			}
			set
			{
				this.named = value;
			}
		}


		public virtual ArchiveData[] Archives
		{
			get
			{
				return archives;
			}
			set
			{
				this.archives = value;
			}
		}

	}

}