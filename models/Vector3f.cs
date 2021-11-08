namespace net.runelite.cache.models
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
			return "Vector3f{" + "x=" + x + ", y=" + y + ", z=" + z + '}';
		}

		public override int GetHashCode()
		{
			int hash = 7;
			hash = 23 * hash + Float.floatToIntBits(this.x);
			hash = 23 * hash + Float.floatToIntBits(this.y);
			hash = 23 * hash + Float.floatToIntBits(this.z);
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
//JAVA TO C# CONVERTER WARNING: The original Java variable was marked 'final':
//ORIGINAL LINE: final Vector3f other = (Vector3f) obj;
			Vector3f other = (Vector3f) obj;
			if (Float.floatToIntBits(this.x) != Float.floatToIntBits(other.x))
			{
				return false;
			}
			if (Float.floatToIntBits(this.y) != Float.floatToIntBits(other.y))
			{
				return false;
			}
			if (Float.floatToIntBits(this.z) != Float.floatToIntBits(other.z))
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

	}

}