package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ReapCropResp
	{
		public static const PROTO:String = "ProtoProduce.ReapCropResp";
		public var package_root:*;
		public  var message:*;
		public var cropland:Vector.<CropLandCPP>;
		public var commons:CommonItemsCPP;
		public var isfull:Boolean;
		public function ReapCropResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			cropland = new Vector.<CropLandCPP>();
			commons = undefined;
			isfull = undefined;
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
			serializeObj.isfull = this.isfull;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReapCropResp
		{
			cropland = new Vector.<CropLandCPP>();
			commons = undefined;
			isfull = undefined;
			for(var i:int = 0;i < msgObj.cropland.length;i++)
			{
				this.cropland.push(new CropLandCPP(package_root).unserialize(msgObj.cropland[i]));
			}
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.isfull = msgObj.isfull;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReapCropResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}