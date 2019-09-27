package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ViewAdRecycleItemResp
	{
		public static const PROTO:String = "ProtoShop.ViewAdRecycleItemResp";
		public var package_root:*;
		public  var message:*;
		public var shop:ShopCPP;
		public var commons:CommonItemsCPP;
		public function ViewAdRecycleItemResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shop = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shop = this.shop.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ViewAdRecycleItemResp
		{
			shop = undefined;
			commons = undefined;
			this.shop = new ShopCPP(package_root).unserialize(msgObj.shop);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ViewAdRecycleItemResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}