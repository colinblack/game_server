package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ServerTime
	{
		public static const PROTO:String = "User.ServerTime";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public function ServerTime(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ServerTime
		{
			ts = undefined;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ServerTime
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}