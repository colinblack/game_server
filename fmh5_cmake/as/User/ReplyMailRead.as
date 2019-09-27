package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ReplyMailRead
	{
		public static const PROTO:String = "User.ReplyMailRead";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var stat:int;
		public function ReplyMailRead(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
			stat = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.stat = this.stat;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyMailRead
		{
			ts = undefined;
			stat = undefined;
			this.ts = msgObj.ts;
			this.stat = msgObj.stat;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyMailRead
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}