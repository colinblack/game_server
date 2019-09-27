package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RequestSysMail
	{
		public static const PROTO:String = "User.RequestSysMail";
		public var package_root:*;
		public  var message:*;
		public function RequestSysMail(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestSysMail
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestSysMail
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}