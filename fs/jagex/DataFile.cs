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
using System.IO;

namespace OSRSCache.fs.jagex
{


	public class DataFile : System.IDisposable
	{
		private const int SECTOR_SIZE = 520;

		private readonly RandomAccessFile dat;

		public DataFile(string file)
		{
			this.dat = new RandomAccessFile(file, "rw");
		}

		public virtual void Dispose()
		{
			dat.close();
		}

		public virtual void clear()
		{
			dat.setLength(0L);
		}

		/// <param name="indexId"> expected index of archive of contents being read </param>
		/// <param name="archiveId"> expected archive of contents being read </param>
		/// <param name="sector"> sector to start reading at </param>
		/// <param name="size"> size of file
		/// @return </param>
		public virtual byte[] read(int indexId, int archiveId, int sector, int size)
		{
			lock (this)
			{
				if (sector <= 0L || dat.length() / SECTOR_SIZE < (long) sector)
				{
					Console.WriteLine("bad read, dat length {0}, requested sector {1}", dat.length(), sector);
					return null;
				}
        
				byte[] readBuffer = new byte[SECTOR_SIZE];
				ByteBuffer buffer = ByteBuffer.allocate(size);
        
				for (int part = 0, readBytesCount = 0, nextSector; size > readBytesCount; sector = nextSector)
				{
					if (sector == 0)
					{
						Console.WriteLine("Unexpected end of file");
						return null;
					}
        
					dat.seek(SECTOR_SIZE * sector);
        
					int dataBlockSize = size - readBytesCount;
					byte headerSize;
					int currentIndex;
					int currentPart;
					int currentArchive;
					if (archiveId > 0xFFFF)
					{
						headerSize = 10;
						if (dataBlockSize > SECTOR_SIZE - headerSize)
						{
							dataBlockSize = SECTOR_SIZE - headerSize;
						}
        
						int i = dat.read(readBuffer, 0, headerSize + dataBlockSize);
						if (i != headerSize + dataBlockSize)
						{
							Console.WriteLine("Short read when reading file data for {0}/{1}", indexId, archiveId);
							return null;
						}
        
						currentArchive = ((readBuffer[0] & 0xFF) << 24) | ((readBuffer[1] & 0xFF) << 16) | ((readBuffer[2] & 0xFF) << 8) | (readBuffer[3] & 0xFF);
						currentPart = ((readBuffer[4] & 0xFF) << 8) + (readBuffer[5] & 0xFF);
						nextSector = ((readBuffer[6] & 0xFF) << 16) | ((readBuffer[7] & 0xFF) << 8) | (readBuffer[8] & 0xFF);
						currentIndex = readBuffer[9] & 0xFF;
					}
					else
					{
						headerSize = 8;
						if (dataBlockSize > SECTOR_SIZE - headerSize)
						{
							dataBlockSize = SECTOR_SIZE - headerSize;
						}
        
						int i = dat.read(readBuffer, 0, headerSize + dataBlockSize);
						if (i != headerSize + dataBlockSize)
						{
							Console.WriteLine("short read");
							return null;
						}
        
						currentArchive = ((readBuffer[0] & 0xFF) << 8) | (readBuffer[1] & 0xFF);
						currentPart = ((readBuffer[2] & 0xFF) << 8) | (readBuffer[3] & 0xFF);
						nextSector = ((readBuffer[4] & 0xFF) << 16) | ((readBuffer[5] & 0xFF) << 8) | (readBuffer[6] & 0xFF);
						currentIndex = readBuffer[7] & 0xFF;
					}
        
					if (archiveId != currentArchive || currentPart != part || indexId != currentIndex)
					{
						Console.WriteLine("data mismatch {0} != {1}, {2} != {3}, {4} != {5}", archiveId, currentArchive, part, currentPart, indexId, currentIndex);
						return null;
					}
        
					if (nextSector < 0 || dat.length() / SECTOR_SIZE < (long) nextSector)
					{
						Console.WriteLine("Invalid next sector");
						return null;
					}
        
					buffer.put(readBuffer, headerSize, dataBlockSize);
					readBytesCount += dataBlockSize;
        
					++part;
				}
        
				buffer.flip();
				return buffer.array();
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public synchronized DataFileWriteResult write(int indexId, int archiveId, byte[] compressedData) throws java.io.IOException
		public virtual DataFileWriteResult write(int indexId, int archiveId, byte[] compressedData)
		{
			lock (this)
			{
				int sector;
				int startSector;
        
				byte[] writeBuffer = new byte[SECTOR_SIZE];
				ByteBuffer data = ByteBuffer.wrap(compressedData);
        
				sector = (int)((dat.length() + (long)(SECTOR_SIZE - 1)) / (long) SECTOR_SIZE);
				if (sector == 0)
				{
					sector = 1;
				}
				startSector = sector;
        
				for (int part = 0; data.hasRemaining(); ++part)
				{
					int nextSector = sector + 1; // we always just append sectors
					int dataToWrite;
        
					if (0xFFFF < archiveId)
					{
						if (data.remaining() <= 510)
						{
							nextSector = 0;
						}
        
						writeBuffer[0] = (byte)(archiveId >> 24);
						writeBuffer[1] = (byte)(archiveId >> 16);
						writeBuffer[2] = (byte)(archiveId >> 8);
						writeBuffer[3] = (byte) archiveId;
						writeBuffer[4] = (byte)(part >> 8);
						writeBuffer[5] = (byte) part;
						writeBuffer[6] = (byte)(nextSector >> 16);
						writeBuffer[7] = (byte)(nextSector >> 8);
						writeBuffer[8] = (byte) nextSector;
						writeBuffer[9] = (byte) indexId;
						dat.seek(SECTOR_SIZE * sector);
						dat.write(writeBuffer, 0, 10);
        
						dataToWrite = data.remaining();
						if (dataToWrite > 510)
						{
							dataToWrite = 510;
						}
					}
					else
					{
						if (data.remaining() <= 512)
						{
							nextSector = 0;
						}
        
						writeBuffer[0] = (byte)(archiveId >> 8);
						writeBuffer[1] = (byte) archiveId;
						writeBuffer[2] = (byte)(part >> 8);
						writeBuffer[3] = (byte) part;
						writeBuffer[4] = (byte)(nextSector >> 16);
						writeBuffer[5] = (byte)(nextSector >> 8);
						writeBuffer[6] = (byte) nextSector;
						writeBuffer[7] = (byte) indexId;
						dat.seek(SECTOR_SIZE * sector);
						dat.write(writeBuffer, 0, 8);
        
						dataToWrite = data.remaining();
						if (dataToWrite > 512)
						{
							dataToWrite = 512;
						}
					}
        
					data.get(writeBuffer, 0, dataToWrite);
					dat.write(writeBuffer, 0, dataToWrite);
					sector = nextSector;
				}
        
				DataFileWriteResult res = new DataFileWriteResult();
				res.sector = startSector;
				res.compressedLength = compressedData.Length;
				return res;
			}
		}
	}

}