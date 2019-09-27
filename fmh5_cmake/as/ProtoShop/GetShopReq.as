package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class GetShopReq
	{
		public static const PROTO:String = "ProtoShop.GetShopReq";
		public var package_root:*;
		public  var message:*;
		public function GetShopReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetShopReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetShopReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}