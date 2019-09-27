package com.sanguo.game.server.connectlogic.common.message.Common
{
	import laya.utils.Byte;
	public class ReplyPay
	{
		public static const PROTO:String = "Common.ReplyPay";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public var name:Byte;
		public function ReplyPay(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ret = this.ret;
			if(this.name!= undefined)
			{
				serializeObj.name = this.name.getUint8Array(0, this.name.length);
				this.name.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyPay
		{
			ret = undefined;
			name = undefined;
			this.ret = msgObj.ret;
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = new Byte();
				this.name.writeArrayBuffer(msgObj.name);
				this.name.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyPay
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}