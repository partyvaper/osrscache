namespace OSRSCache.definitions
{
	using ScriptVarType = OSRSCache.util.ScriptVarType;

	public class ParamDefinition
	{
		public ScriptVarType type; // all was private now is public
		public bool isMembers = true;
		public int defaultInt;
		public string defaultString;
	}

}