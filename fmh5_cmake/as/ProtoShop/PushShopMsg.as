package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class PushShopMsg
	{
		public static const PROTO:String = "ProtoShop.PushShopMsg";
		public var package_root:*;
		public  var message:*;
		public var shop:ShopCPP;
		public function PushShopMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shop = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shop = this.shop.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushShopMsg
		{
			shop = undefined;
			this.shop = new ShopCPP(package_root).unserialize(msgObj.shop);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushShopMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}