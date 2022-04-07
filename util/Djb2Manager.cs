using System;
using System.Collections.Generic;
using JavaPropertiesParser;
using JavaPropertiesParser.Expressions;

namespace OSRSCache.util
{


	public class Djb2Manager
	{
		private readonly IDictionary<int, string> hashes = new Dictionary<int, string>();

		public virtual void load()
		{
			// Properties properties = new Properties();
			// properties.load(typeof(Djb2Manager).getResourceAsStream("/djb2.properties"));
			Document document = Parser.Parse("/djb2.properties");
			
			foreach (object key in document.Expressions)
			{
				Console.WriteLine($"document.Expressions, key: {key}");
				int hash = int.Parse((string) key);
				string value = ""; // TODO: properties.getProperty((string) key);
			
				hashes[hash] = value;
			}

			Console.WriteLine("Loaded {0} djb2 hashes", hashes.Count);
		}

		public virtual string getName(int hash)
		{
			return hashes[hash];
		}
	}

}