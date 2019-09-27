package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RequestMailGet
	{
		public static const PROTO:String = "User.RequestMailGet";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public function RequestMailGet(root:*)
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
		public function unserialize(msgObj:*):RequestMailGet
		{
			ts = undefined;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestMailGet
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}