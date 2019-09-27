package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class DaliyShareReq
	{
		public static const PROTO:String = "User.DaliyShareReq";
		public var package_root:*;
		public  var message:*;
		public function DaliyShareReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):DaliyShareReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DaliyShareReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}