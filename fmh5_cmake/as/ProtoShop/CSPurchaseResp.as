package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class CSPurchaseResp
	{
		public static const PROTO:String = "ProtoShop.CSPurchaseResp";
		public var package_root:*;
		public  var message:*;
		public var visitUid:int;
		public var visitedUid:int;
		public var visitedshop:ShopCPP;
		public function CSPurchaseResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			visitUid = undefined;
			visitedUid = undefined;
			visitedshop = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.visitUid = this.visitUid;
			serializeObj.visitedUid = this.visitedUid;
			serializeObj.visitedshop = this.visitedshop.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSPurchaseResp
		{
			visitUid = undefined;
			visitedUid = undefined;
			visitedshop = undefined;
			this.visitUid = msgObj.visitUid;
			this.visitedUid = msgObj.visitedUid;
			this.visitedshop = new ShopCPP(package_root).unserialize(msgObj.visitedshop);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSPurchaseResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}