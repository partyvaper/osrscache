using System.Collections.Generic;

namespace OSRSCache.definitions
{
	public class ObjectDefinition
	{
		// all was private, is now public
		public int id;
		public short[] retextureToFind;
		public int decorDisplacement = 16;
		public bool isHollow = false;
		public string name = "null";
		public int[] objectModels;
		public int[] objectTypes;
		public short[] recolorToFind;
		public int mapAreaId = -1;
		public short[] textureToReplace;
		public int sizeX = 1;
		public int sizeY = 1;
		public int anInt2083 = 0;
		public int[] ambientSoundIds;
		public int offsetX = 0;
		public bool mergeNormals = false;
		public int wallOrDoor = -1;
		public int animationID = -1;
		public int varbitID = -1;
		public int ambient = 0;
		public int contrast = 0;
		public string[] actions = new string[5];
		public int interactType = 2;
		public int mapSceneID = -1;
		public int blockingMask = 0;
		public short[] recolorToReplace;
		public bool shadow = true;
		public int modelSizeX = 128;
		public int modelSizeHeight = 128;
		public int modelSizeY = 128;
		public int objectID;
		public int offsetHeight = 0;
		public int offsetY = 0;
		public bool obstructsGround = false;
		public int contouredGround = -1;
		public int supportsItems = -1;
		public int[] configChangeDest;
		public int category;
		public bool isRotated = false;
		public int varpID = -1;
		public int ambientSoundId = -1;
		public bool aBool2111 = false;
		public int anInt2112 = 0;
		public int anInt2113 = 0;
		public bool blocksProjectile = true;
		public bool randomizeAnimStart;
		public IDictionary<int, object> @params = null;
	}

}