﻿using System.Collections.Generic;

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
namespace OSRSCache.util
{
	// TODO: Rewrite this whole file !?

	public class XteaKeyManager
	{
		private readonly IDictionary<int, int[]> keys = new Dictionary<int, int[]>();

		public virtual void loadKeys()
		{
			// TODO: JSON LOADER AND PARSER !!!!!
			// XteaClient xteaClient = new XteaClient(RuneLiteAPI.CLIENT);
			//
			// try
			// {
			// 	foreach (XteaKey key in xteaClient.get())
			// 	{
			// 		keys[key.getRegion()] = key.getKeys();
			// 	}
			// }
			// catch (IOException ex)
			// {
			// 	// happens on release when it is not deployed yet
			// 	Console.WriteLine("unable to load xtea keys", ex);
			// 	return;
			// }
			//
			// Console.WriteLine("Loaded {} keys", keys.Count);
		}

		public virtual int[] getKeys(int region)
		{
			return keys[region];
		}
	}

}