using System;
using System.Collections.Generic;

// import java.util.ArrayList;
// import java.util.List;
// import java.util.Objects;
using OSRSCache.index.ArchiveData;
using OSRSCache.index.FileData;
using OSRSCache.index.IndexData;
using OSRSCache.util.Djb2;

namespace OSRSCache.fs
{

	public class Index
	{
		private readonly int id;

		private int protocol = 6;
		private bool named = true;
		private int revision;
		private int crc;
		private int compression; // compression method of this index's data in 255

		private readonly List<Archive> archives = new ArrayList<>();

		public Index(int id)
		{
			this.id = id;
		}

		// @Override

		public int hashCode()
		{
			int hash = 3;
			hash = 97 * hash + this.id;
			hash = 97 * hash + this.revision;
			hash = 97 * hash + Objects.hashCode(this.archives);
			return hash;
		}

		// @Override

		public bool equals(Object obj)
		{
			if (obj == null)
			{
				return false;
			}

			if (getClass() != obj.getClass())
			{
				return false;
			}

			final Index other = (Index) obj;
			if (this.id != other.id)
			{
				return false;
			}

			if (this.revision != other.revision)
			{
				return false;
			}

			if (!Objects.equals(this.archives, other.archives))
			{
				return false;
			}

			return true;
		}

		public int getId()
		{
			return id;
		}

		public int getProtocol()
		{
			return protocol;
		}

		public void setProtocol(int protocol)
		{
			this.protocol = protocol;
		}

		public bool isNamed()
		{
			return named;
		}

		public void setNamed(boolean named)
		{
			this.named = named;
		}

		public int getRevision()
		{
			return revision;
		}

		public void setRevision(int revision)
		{
			this.revision = revision;
		}

		public int getCrc()
		{
			return crc;
		}

		public void setCrc(int crc)
		{
			this.crc = crc;
		}

		public int getCompression()
		{
			return compression;
		}

		public void setCompression(int compression)
		{
			this.compression = compression;
		}

		public List<Archive> getArchives()
		{
			return archives;
		}

		public Archive addArchive(int id)
		{
			Archive archive = new Archive(this, id);
			this.archives.add(archive);
			return archive;
		}

		public Archive getArchive(int id)
		{
			for (Archive a :
			archives)
			{
				if (a.getArchiveId() == id)
				{
					return a;
				}
			}
			return null;
		}

		public Archive findArchiveByName(string name)
		{
			int hash = Djb2.hash(name);
			for (Archive a :
			archives)
			{
				if (a.getNameHash() == hash)
				{
					return a;
				}
			}
			return null;
		}

		public IndexData toIndexData()
		{
			IndexData data = new IndexData();
			data.setProtocol(protocol);
			data.setRevision(revision);
			data.setNamed(named);

			ArchiveData[] archiveDatas = new ArchiveData[archives.size()];
			data.setArchives(archiveDatas);

			int idx = 0;
			for (Archive archive :
			archives)
			{
				ArchiveData ad = archiveDatas[idx++] = new ArchiveData();
				ad.setId(archive.getArchiveId());
				ad.setNameHash(archive.getNameHash());
				ad.setCrc(archive.getCrc());
				ad.setRevision(archive.getRevision());

				FileData[] files = archive.getFileData();
				ad.setFiles(files);
			}
			return data;
		}
	}
}