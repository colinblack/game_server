package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ConfirmPaymentReq
	{
		public static const PROTO:String = "ProtoShop.ConfirmPaymentReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var type:int;
		public function ConfirmPaymentReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			if(this.type!= undefined)
			{
				serializeObj.type = this.type;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ConfirmPaymentReq
		{
			ud = undefined;
			type = undefined;
			this.ud = msgObj.ud;
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
		public function decode(buffer:*):ConfirmPaymentReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}