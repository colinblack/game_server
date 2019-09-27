package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class PurchaseCoinReq
	{
		public static const PROTO:String = "User.PurchaseCoinReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function PurchaseCoinReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PurchaseCoinReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PurchaseCoinReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}