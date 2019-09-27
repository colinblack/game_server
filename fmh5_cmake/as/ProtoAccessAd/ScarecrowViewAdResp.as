package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class ScarecrowViewAdResp
	{
		public static const PROTO:String = "ProtoAccessAd.ScarecrowViewAdResp";
		public var package_root:*;
		public  var message:*;
		public var scarecrow:ScarecrowCPP;
		public var cropland:Vector.<CropLandCPP>;
		public var commons:CommonItemsCPP;
		public function ScarecrowViewAdResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			scarecrow = undefined;
			cropland = new Vector.<CropLandCPP>();
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.scarecrow = this.scarecrow.serialize();
			serializeObj.cropland = [];
			for(var i:int = 0;i < this.cropland.length;i++)
			{
				serializeObj.cropland.push(this.cropland[i].serialize());
			}
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ScarecrowViewAdResp
		{
			scarecrow = undefined;
			cropland = new Vector.<CropLandCPP>();
			commons = undefined;
			this.scarecrow = new ScarecrowCPP(package_root).unserialize(msgObj.scarecrow);
			for(var i:int = 0;i < msgObj.cropland.length;i++)
			{
				this.cropland.push(new CropLandCPP(package_root).unserialize(msgObj.cropland[i]));
			}
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ScarecrowViewAdResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}