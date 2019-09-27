package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ModifyShelfInfoResp
	{
		public static const PROTO:String = "ProtoShop.ModifyShelfInfoResp";
		public var package_root:*;
		public  var message:*;
		public var shop:ShopCPP;
		public var commons:CommonItemsCPP;
		public var ts:int;
		public function ModifyShelfInfoResp(root:*)
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
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			if(this.ts!= undefined)
			{
				serializeObj.ts = this.ts;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ModifyShelfInfoResp
		{
			shop = undefined;
			commons = undefined;
			ts = undefined;
			this.shop = new ShopCPP(package_root).unserialize(msgObj.shop);
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
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
		public function decode(buffer:*):ModifyShelfInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}