package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ChargeItem
	{
		public static const PROTO:String = "User.ChargeItem";
		public var package_root:*;
		public  var message:*;
		public var cash:int;
		public var ts:int;
		public function ChargeItem(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			cash = undefined;
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cash = this.cash;
			serializeObj.ts = this.ts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ChargeItem
		{
			cash = undefined;
			ts = undefined;
			this.cash = msgObj.cash;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ChargeItem
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}