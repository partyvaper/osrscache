using System.Collections.Generic;

namespace OSRSCache.definitions.savers
{
	using ObjectDefinition = OSRSCache.definitions.ObjectDefinition;
	using OutputStream = OSRSCache.io.OutputStream;

	public class ObjectSaver
	{
		public virtual sbyte[] save(ObjectDefinition obj)
		{
			OutputStream @out = new OutputStream();
			if (obj.objectTypes != null && obj.objectModels != null)
			{
				@out.writeByte(1);
				@out.writeByte(obj.objectTypes.Length);
				for (int i = 0; i < obj.objectTypes.Length; ++i)
				{
					@out.writeShort(obj.objectModels[i]);
					@out.writeByte(obj.objectTypes[i]);
				}
			}
			if (obj.name != null)
			{
				@out.writeByte(2);
				@out.writeString(obj.name);
			}
			if (obj.objectTypes == null && obj.objectModels != null)
			{
				@out.writeByte(5);
				@out.writeByte(obj.objectModels.Length);
				for (int i = 0; i < obj.objectModels.Length; ++i)
				{
					@out.writeShort(obj.objectModels[i]);
				}
			}
			@out.writeByte(14);
			@out.writeByte(obj.sizeX);
			@out.writeByte(15);
			@out.writeByte(obj.sizeY);
			if (obj.interactType == 0 && !obj.blocksProjectile)
			{
				@out.writeByte(17);
			}
			else if (!obj.blocksProjectile)
			{
				@out.writeByte(18);
			}
			if (obj.wallOrDoor != -1)
			{
				@out.writeByte(19);
				@out.writeByte(obj.wallOrDoor);
			}
			if (obj.contouredGround == 0)
			{
				@out.writeByte(21);
			}
			if (!obj.mergeNormals)
			{
				@out.writeByte(22);
			}
			if (obj.aBool2111)
			{
				@out.writeByte(23);
			}
			if (obj.animationID != -1)
			{
				@out.writeByte(24);
				@out.writeShort(obj.animationID);
			}
			if (obj.interactType == 1)
			{
				@out.writeByte(27);
			}
			@out.writeByte(28);
			@out.writeByte(obj.decorDisplacement);
			@out.writeByte(29);
			@out.writeByte(obj.ambient);
			@out.writeByte(39);
			@out.writeByte(obj.contrast / 25);
			for (int i = 0; i < 5; ++i)
			{
				@out.writeByte(30 + i);
				string action = obj.actions[i];
				@out.writeString(!string.ReferenceEquals(action, null) ? action : "Hidden");
			}
			if (obj.recolorToFind != null && obj.recolorToReplace != null)
			{
				@out.writeByte(40);
				@out.writeByte(obj.recolorToFind.Length);
				for (int i = 0; i < obj.recolorToFind.Length; ++i)
				{
					@out.writeShort(obj.recolorToFind[i]);
					@out.writeShort(obj.recolorToReplace[i]);
				}
			}
			if (obj.retextureToFind != null && obj.textureToReplace != null)
			{
				@out.writeByte(41);
				@out.writeByte(obj.retextureToFind.Length);
				for (int i = 0; i < obj.retextureToFind.Length; ++i)
				{
					@out.writeShort(obj.retextureToFind[i]);
					@out.writeShort(obj.textureToReplace[i]);
				}
			}
			if (obj.isRotated)
			{
				@out.writeByte(62);
			}
			if (!obj.shadow)
			{
				@out.writeByte(64);
			}
			@out.writeByte(65);
			@out.writeShort(obj.modelSizeX);
			@out.writeByte(66);
			@out.writeShort(obj.modelSizeHeight);
			@out.writeByte(67);
			@out.writeShort(obj.modelSizeY);
			if (obj.mapSceneID != -1)
			{
				@out.writeByte(68);
				@out.writeShort(obj.mapSceneID);
			}
			if (obj.blockingMask != 0)
			{
				@out.writeByte(69);
				@out.writeByte(obj.blockingMask);
			}
			@out.writeByte(70);
			@out.writeShort(obj.offsetX);
			@out.writeByte(71);
			@out.writeShort(obj.offsetHeight);
			@out.writeByte(72);
			@out.writeShort(obj.offsetY);
			if (obj.obstructsGround)
			{
				@out.writeByte(73);
			}
			if (obj.isHollow)
			{
				@out.writeByte(74);
			}
			if (obj.supportsItems != -1)
			{
				@out.writeByte(75);
				@out.writeByte(obj.supportsItems);
			}
			if (obj.ambientSoundId != -1)
			{
				@out.writeByte(78);
				@out.writeShort(obj.ambientSoundId);
				@out.writeByte(obj.anInt2083);
			}
			if (obj.ambientSoundIds != null)
			{
				@out.writeByte(79);
				@out.writeShort(obj.anInt2112);
				@out.writeShort(obj.anInt2113);
				@out.writeByte(obj.anInt2083);
				@out.writeByte(obj.ambientSoundIds.Length);
				foreach (int i in obj.ambientSoundIds)
				{
					@out.writeShort(i);
				}
			}
			if (obj.contouredGround != -1)
			{
				@out.writeByte(81);
				@out.writeByte(obj.contouredGround / 256);
			}
			if (obj.mapAreaId != -1)
			{
				@out.writeByte(82);
				@out.writeShort(obj.mapAreaId);
			}
			if (obj.configChangeDest != null)
			{
				@out.writeByte(92);
				@out.writeShort(obj.varbitID);
				@out.writeShort(obj.varpID);

				int[] c = obj.configChangeDest;
				@out.writeShort(c[c.Length - 1]);
				@out.writeByte(c.Length - 2);
				for (int i = 0; i <= c.Length - 2; ++i)
				{
					@out.writeShort(c[i]);
				}
			}
			if (obj.@params != null)
			{
				@out.writeByte(249);
				@out.writeByte(obj.@params.Count);
				foreach (KeyValuePair<int, object> entry in obj.@params.SetOfKeyValuePairs())
				{
					@out.writeByte(entry.Value is string ? 1 : 0);
					@out.write24BitInt(entry.Key);
					if (entry.Value is string)
					{
						@out.writeString((string) entry.Value);
					}
					else
					{
						@out.writeInt(((int?) entry.Value).Value);
					}
				}
			}
			@out.writeByte(0);
			return @out.flip();
		}
	}

}