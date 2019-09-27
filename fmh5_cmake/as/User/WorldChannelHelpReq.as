package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class WorldChannelHelpReq
	{
		public static const PROTO:String = "User.WorldChannelHelpReq";
		public var package_root:*;
		public  var message:*;
		public function WorldChannelHelpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):WorldChannelHelpReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):WorldChannelHelpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}