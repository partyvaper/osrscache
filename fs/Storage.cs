namespace OSRSCache.fs
{

	public interface Storage // : AutoCloseable
	{
		void init(Store store);

		void close();

		void load(Store store);

		void save(Store store);

		byte[] loadArchive(Archive archive);

		void saveArchive(Archive archive, byte[] data);
	}

}