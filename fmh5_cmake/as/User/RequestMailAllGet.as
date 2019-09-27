package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RequestMailAllGet
	{
		public static const PROTO:String = "User.RequestMailAllGet";
		public var package_root:*;
		public  var message:*;
		public function RequestMailAllGet(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestMailAllGet
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestMailAllGet
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}