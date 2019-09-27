package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class PlantCropReq
	{
		public static const PROTO:String = "ProtoProduce.PlantCropReq";
		public var package_root:*;
		public  var message:*;
		public var uds:Vector.<int>;
		public var plant:int;
		public function PlantCropReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uds = new Vector.<int>();
			plant = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uds = [];
			for(var i:int = 0;i < this.uds.length;i++)
			{
				serializeObj.uds.push(this.uds[i]);
			}
			serializeObj.plant = this.plant;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PlantCropReq
		{
			uds = new Vector.<int>();
			plant = undefined;
			for(var i:int = 0;i < msgObj.uds.length;i++)
			{
				this.uds.push(msgObj.uds[i]);
			}
			this.plant = msgObj.plant;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PlantCropReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}