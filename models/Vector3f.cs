using System;

namespace OSRSCache.models
{
	public class Vector3f
	{
		public float x;
		public float y;
		public float z;

		public Vector3f()
		{
		}

		public Vector3f(float x, float y, float z)
		{
			this.x = x;
			this.y = y;
			this.z = z;
		}

		public Vector3f(Vector3f other)
		{
			this.x = other.x;
			this.y = other.y;
			this.z = other.z;
		}

		public override string ToString()
		{
			return $"Vector3f(x={x}, y={y}, z={x})";
		}

		public override int GetHashCode()
		{
			int hash = 7;
			hash = 23 * hash + FloatToIntBits(x);
			hash = 23 * hash + FloatToIntBits(y);
			hash = 23 * hash + FloatToIntBits(z);
			return hash;
		}

		public override bool Equals(object obj)
		{
			if (this == obj)
			{
				return true;
			}
			if (obj == null)
			{
				return false;
			}
			if (this.GetType() != obj.GetType())
			{
				return false;
			}
			Vector3f other = (Vector3f) obj;
			if (FloatToIntBits(x) != FloatToIntBits(other.x))
			{
				return false;
			}
			if (FloatToIntBits(y) != FloatToIntBits(other.y))
			{
				return false;
			}
			if (FloatToIntBits(z) != FloatToIntBits(other.z))
			{
				return false;
			}
			return true;
		}

		public virtual float X
		{
			get
			{
				return x;
			}
			set
			{
				this.x = value;
			}
		}


		public virtual float Y
		{
			get
			{
				return y;
			}
			set
			{
				this.y = value;
			}
		}


		public virtual float Z
		{
			get
			{
				return z;
			}
			set
			{
				this.z = value;
			}
		}

		private static int FloatToIntBits(float f)
		{
			return BitConverter.ToInt32(BitConverter.GetBytes(f), 0);
		}

	}

}