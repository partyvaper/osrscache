using System;
using System.Diagnostics;

namespace OSRSCache.models
{
	public class VertexNormal
	{
		public int x;
		public int y;
		public int z;
		public int magnitude;

		public virtual Vector3f normalize()
		{
			Vector3f v = new Vector3f();

			int length = (int) Math.Sqrt((double)(x * x + y * y + z * z));
			if (length == 0)
			{
				length = 1;
			}

			v.x = (float) x / length;
			v.y = (float) y / length;
			v.z = (float) z / length;

			Debug.Assert(v.x >= -1f && v.x <= 1f);
			Debug.Assert(v.y >= -1f && v.y <= 1f);
			Debug.Assert(v.z >= -1f && v.z <= 1f);

			return v;
		}
	}

}