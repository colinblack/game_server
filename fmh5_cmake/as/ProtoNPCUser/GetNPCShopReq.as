package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class GetNPCShopReq
	{
		public static const PROTO:String = "ProtoNPCUser.GetNPCShopReq";
		public var package_root:*;
		public  var message:*;
		public function GetNPCShopReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNPCShopReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNPCShopReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}