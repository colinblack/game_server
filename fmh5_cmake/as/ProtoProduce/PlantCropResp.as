package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class PlantCropResp
	{
		public static const PROTO:String = "ProtoProduce.PlantCropResp";
		public var package_root:*;
		public  var message:*;
		public var cropland:Vector.<CropLandCPP>;
		public var commons:CommonItemsCPP;
		public function PlantCropResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			cropland = new Vector.<CropLandCPP>();
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cropland = [];
			for(var i:int = 0;i < this.cropland.length;i++)
			{
				serializeObj.cropland.push(this.cropland[i].serialize());
			}
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PlantCropResp
		{
			cropland = new Vector.<CropLandCPP>();
			commons = undefined;
			for(var i:int = 0;i < msgObj.cropland.length;i++)
			{
				this.cropland.push(new CropLandCPP(package_root).unserialize(msgObj.cropland[i]));
			}
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PlantCropResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}