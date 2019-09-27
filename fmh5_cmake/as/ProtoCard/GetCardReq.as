package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class GetCardReq
	{
		public static const PROTO:String = "ProtoCard.GetCardReq";
		public var package_root:*;
		public  var message:*;
		public function GetCardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetCardReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetCardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}