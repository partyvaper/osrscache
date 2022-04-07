using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Text.RegularExpressions;

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
 * Copyright (c) 2018, Joshua Filby <joshua@filby.me>
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

	public class Namer
	{
		private readonly ISet<string> used = new HashSet<string>();

		public virtual string name(string name, int id)
		{
			name = sanitize(name);

			if (string.ReferenceEquals(name, null))
			{
				return null;
			}

			if (used.Contains(name))
			{
				name = $"{name}_{id}";
				Debug.Assert(!used.Contains(name));
			}

			used.Add(name);

			return name;
		}

		private static string sanitize(string @in)
		{
			string s = removeTags(@in).ToUpper().Replace(' ', '_'); // .Replace("[^a-zA-Z0-9_]", "");
			s = Regex.Replace(s, "[^a-zA-Z0-9_]", "");
			if (s.Length == 0)
			{
				return null;
			}
			if (char.IsDigit(s[0]))
			{
				return $"_{s}";
			}
			else
			{
				return s;
			}
		}

		public static string removeTags(string str)
		{
			StringBuilder builder = new StringBuilder(str.Length);
			bool inTag = false;

			for (int i = 0; i < str.Length; i++)
			{
				char currentChar = str[i];

				if (currentChar == '<')
				{
					inTag = true;
				}
				else if (currentChar == '>')
				{
					inTag = false;
				}
				else if (!inTag)
				{
					builder.Append(currentChar);
				}
			}

			return builder.ToString();
		}
	}

}