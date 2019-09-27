package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class PushRandomRewardReq
	{
		public static const PROTO:String = "ProtoProduce.PushRandomRewardReq";
		public var package_root:*;
		public  var message:*;
		public var propsid:int;
		public var commons:CommonItemsCPP;
		public function PushRandomRewardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			propsid = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propsid = this.propsid;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushRandomRewardReq
		{
			propsid = undefined;
			commons = undefined;
			this.propsid = msgObj.propsid;
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
		public function decode(buffer:*):PushRandomRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}