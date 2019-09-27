package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class CSVisitOtherShopResp
	{
		public static const PROTO:String = "ProtoShop.CSVisitOtherShopResp";
		public var package_root:*;
		public  var message:*;
		public var visitUid:int;
		public var visitedShopResp:VisitOtherShopResp;
		public function CSVisitOtherShopResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			visitUid = undefined;
			visitedShopResp = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.visitUid = this.visitUid;
			serializeObj.visitedShopResp = this.visitedShopResp.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSVisitOtherShopResp
		{
			visitUid = undefined;
			visitedShopResp = undefined;
			this.visitUid = msgObj.visitUid;
			this.visitedShopResp = new VisitOtherShopResp(package_root).unserialize(msgObj.visitedShopResp);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSVisitOtherShopResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}