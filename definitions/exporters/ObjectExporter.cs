using System.IO;
using Newtonsoft.Json;

namespace OSRSCache.definitions.exporters
{
	using ObjectDefinition = OSRSCache.definitions.ObjectDefinition;

	public class ObjectExporter
	{
		private readonly ObjectDefinition @object;

		public ObjectExporter(ObjectDefinition @object)
		{
			this.@object = @object;
		}

		public virtual string export()
		{
			return JsonConvert.SerializeObject(@object);
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