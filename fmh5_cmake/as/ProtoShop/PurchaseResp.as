package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class PurchaseResp
	{
		public static const PROTO:String = "ProtoShop.PurchaseResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var othuid:int;
		public var othshop:ShopCPP;
		public function PurchaseResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			othuid = undefined;
			othshop = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.othuid = this.othuid;
			serializeObj.othshop = this.othshop.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PurchaseResp
		{
			commons = undefined;
			othuid = undefined;
			othshop = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.othuid = msgObj.othuid;
			this.othshop = new ShopCPP(package_root).unserialize(msgObj.othshop);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PurchaseResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}