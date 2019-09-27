package com.sanguo.game.server.connectlogic.common.message.ProtoRandomBox
{
	import laya.utils.Byte;
	public class BuyBoxGiftReq
	{
		public static const PROTO:String = "ProtoRandomBox.BuyBoxGiftReq";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public function BuyBoxGiftReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.type!= undefined)
			{
				serializeObj.type = this.type;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyBoxGiftReq
		{
			type = undefined;
			if(msgObj.hasOwnProperty("type"))
			{
				this.type = msgObj.type;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyBoxGiftReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}