namespace net.runelite.cache.util
{
	/// <summary>
	/// An implementation of the {@code djb2} hash function.
	/// 
	/// @author Graham
	/// @author `Discardedx2
	/// </summary>
	public sealed class Djb2
	{
		/// <summary>
		/// An implementation of Dan Bernstein's {@code djb2} hash function which
		/// is slightly modified. Instead of the initial hash being 5381, it is
		/// zero.
		/// </summary>
		/// <param name="str"> The string to hash. </param>
		/// <returns> The hash code. </returns>
		public static int hash(string str)
		{
			int hash = 0;
			for (int i = 0; i < str.Length; i++)
			{
				hash = str[i] + ((hash << 5) - hash);
			}
			return hash;
		}
	}

}