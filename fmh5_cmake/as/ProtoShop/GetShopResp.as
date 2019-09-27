package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class GetShopResp
	{
		public static const PROTO:String = "ProtoShop.GetShopResp";
		public var package_root:*;
		public  var message:*;
		public var shop:Vector.<ShopCPP>;
		public function GetShopResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shop = new Vector.<ShopCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shop = [];
			for(var i:int = 0;i < this.shop.length;i++)
			{
				serializeObj.shop.push(this.shop[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetShopResp
		{
			shop = new Vector.<ShopCPP>();
			for(var i:int = 0;i < msgObj.shop.length;i++)
			{
				this.shop.push(new ShopCPP(package_root).unserialize(msgObj.shop[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetShopResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}