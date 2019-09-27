package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class HeartBeatReq
	{
		public static const PROTO:String = "User.HeartBeatReq";
		public var package_root:*;
		public  var message:*;
		public function HeartBeatReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):HeartBeatReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HeartBeatReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}