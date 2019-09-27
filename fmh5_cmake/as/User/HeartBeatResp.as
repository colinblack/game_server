package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class HeartBeatResp
	{
		public static const PROTO:String = "User.HeartBeatResp";
		public var package_root:*;
		public  var message:*;
		public function HeartBeatResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):HeartBeatResp
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HeartBeatResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}