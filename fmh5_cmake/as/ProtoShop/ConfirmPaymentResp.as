package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ConfirmPaymentResp
	{
		public static const PROTO:String = "ProtoShop.ConfirmPaymentResp";
		public var package_root:*;
		public  var message:*;
		public var shop:ShopCPP;
		public var commons:CommonItemsCPP;
		public function ConfirmPaymentResp(root:*)
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
		public function unserialize(msgObj:*):ConfirmPaymentResp
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
		public function decode(buffer:*):ConfirmPaymentResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}