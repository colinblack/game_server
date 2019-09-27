package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class BuyShopItemBySystemResp
	{
		public static const PROTO:String = "ProtoShop.BuyShopItemBySystemResp";
		public var package_root:*;
		public  var message:*;
		public var shop:ShopCPP;
		public function BuyShopItemBySystemResp(root:*)
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
		public function unserialize(msgObj:*):BuyShopItemBySystemResp
		{
			shop = undefined;
			this.shop = new ShopCPP(package_root).unserialize(msgObj.shop);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyShopItemBySystemResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}