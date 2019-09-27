package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class RandomVIPGiftReq
	{
		public static const PROTO:String = "ProtoVIP.RandomVIPGiftReq";
		public var package_root:*;
		public  var message:*;
		public function RandomVIPGiftReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RandomVIPGiftReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RandomVIPGiftReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}