package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class ReplyAddCash
	{
		public static const PROTO:String = "Admin.ReplyAddCash";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var cash:int;
		public function ReplyAddCash(root:*)
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
		public function unserialize(msgObj:*):ReplyAddCash
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
		public function decode(buffer:*):ReplyAddCash
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}