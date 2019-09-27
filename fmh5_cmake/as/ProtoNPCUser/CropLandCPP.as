package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class CropLandCPP
	{
		public static const PROTO:String = "ProtoNPCUser.CropLandCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var plant:int;
		public var status:int;
		public var harvestTime:int;
		public function CropLandCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			plant = undefined;
			status = undefined;
			harvestTime = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.plant = this.plant;
			serializeObj.status = this.status;
			serializeObj.harvestTime = this.harvestTime;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CropLandCPP
		{
			ud = undefined;
			plant = undefined;
			status = undefined;
			harvestTime = undefined;
			this.ud = msgObj.ud;
			this.plant = msgObj.plant;
			this.status = msgObj.status;
			this.harvestTime = msgObj.harvestTime;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CropLandCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}