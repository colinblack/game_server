package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class CSVisitOtherShopReq
	{
		public static const PROTO:String = "ProtoShop.CSVisitOtherShopReq";
		public var package_root:*;
		public  var message:*;
		public var visitUid:int;
		public var visitedUid:int;
		public function CSVisitOtherShopReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			visitUid = undefined;
			visitedUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.visitUid = this.visitUid;
			serializeObj.visitedUid = this.visitedUid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSVisitOtherShopReq
		{
			visitUid = undefined;
			visitedUid = undefined;
			this.visitUid = msgObj.visitUid;
			this.visitedUid = msgObj.visitedUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSVisitOtherShopReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}