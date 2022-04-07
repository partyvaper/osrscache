using System.IO;
using Newtonsoft.Json;

namespace OSRSCache.definitions.exporters
{
	using ItemDefinition = OSRSCache.definitions.ItemDefinition;

	public class ItemExporter
	{
		private readonly ItemDefinition item;

		public ItemExporter(ItemDefinition item)
		{
			this.item = item;
		}

		public virtual string export()
		{
			return JsonConvert.SerializeObject(item);
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