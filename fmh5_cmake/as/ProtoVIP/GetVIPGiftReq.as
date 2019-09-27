package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class GetVIPGiftReq
	{
		public static const PROTO:String = "ProtoVIP.GetVIPGiftReq";
		public var package_root:*;
		public  var message:*;
		public function GetVIPGiftReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetVIPGiftReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetVIPGiftReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}