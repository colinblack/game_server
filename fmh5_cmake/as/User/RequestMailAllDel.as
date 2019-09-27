package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RequestMailAllDel
	{
		public static const PROTO:String = "User.RequestMailAllDel";
		public var package_root:*;
		public  var message:*;
		public function RequestMailAllDel(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestMailAllDel
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestMailAllDel
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}