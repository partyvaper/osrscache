using System.Collections.Generic;

namespace OSRSCache.definitions
{

	public class ScriptDefinition
	{
		public int id; // all was private, now is public
		public int[] instructions;
		public int[] intOperands;
		public string[] stringOperands;
		public int intStackCount;
		public int stringStackCount;
		public int localIntCount;
		public int localStringCount;
		public IDictionary<int, int>[] switches;

		public ScriptDefinition(int id)
		{
			this.id = id;
		}
	}

}