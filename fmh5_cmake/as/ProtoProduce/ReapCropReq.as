package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ReapCropReq
	{
		public static const PROTO:String = "ProtoProduce.ReapCropReq";
		public var package_root:*;
		public  var message:*;
		public var uds:Vector.<int>;
		public function ReapCropReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uds = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uds = [];
			for(var i:int = 0;i < this.uds.length;i++)
			{
				serializeObj.uds.push(this.uds[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReapCropReq
		{
			uds = new Vector.<int>();
			for(var i:int = 0;i < msgObj.uds.length;i++)
			{
				this.uds.push(msgObj.uds[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReapCropReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}