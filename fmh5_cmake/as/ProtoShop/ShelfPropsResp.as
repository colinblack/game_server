package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ShelfPropsResp
	{
		public static const PROTO:String = "ProtoShop.ShelfPropsResp";
		public var package_root:*;
		public  var message:*;
		public var shop:ShopCPP;
		public var commons:CommonItemsCPP;
		public var ts:int;
		public function ShelfPropsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shop = undefined;
			commons = undefined;
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shop = this.shop.serialize();
			serializeObj.commons = this.commons.serialize();
			if(this.ts!= undefined)
			{
				serializeObj.ts = this.ts;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShelfPropsResp
		{
			shop = undefined;
			commons = undefined;
			ts = undefined;
			this.shop = new ShopCPP(package_root).unserialize(msgObj.shop);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			if(msgObj.hasOwnProperty("ts"))
			{
				this.ts = msgObj.ts;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShelfPropsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}