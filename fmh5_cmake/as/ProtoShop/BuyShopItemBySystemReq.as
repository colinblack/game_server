package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class BuyShopItemBySystemReq
	{
		public static const PROTO:String = "ProtoShop.BuyShopItemBySystemReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public function BuyShopItemBySystemReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyShopItemBySystemReq
		{
			ud = undefined;
			this.ud = msgObj.ud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyShopItemBySystemReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}