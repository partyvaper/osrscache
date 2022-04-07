using System.IO;
using Newtonsoft.Json;

namespace OSRSCache.definitions.exporters
{
	using NpcDefinition = OSRSCache.definitions.NpcDefinition;

	public class NpcExporter
	{
		private readonly NpcDefinition npc;

		public NpcExporter(NpcDefinition npc)
		{
			this.npc = npc;
		}

		public virtual string export()
		{
			return JsonConvert.SerializeObject(npc);
		}

		public virtual void exportTo(string file)
		{
			using (StreamWriter fw = new StreamWriter(file))
			{
				fw.Write(export());
			}
		}
	}

}