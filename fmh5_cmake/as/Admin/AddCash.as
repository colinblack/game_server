package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class AddCash
	{
		public static const PROTO:String = "Admin.AddCash";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var cash:int;
		public function AddCash(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			cash = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.cash = this.cash;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AddCash
		{
			uid = undefined;
			cash = undefined;
			this.uid = msgObj.uid;
			this.cash = msgObj.cash;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AddCash
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}