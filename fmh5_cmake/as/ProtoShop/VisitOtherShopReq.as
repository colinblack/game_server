package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class VisitOtherShopReq
	{
		public static const PROTO:String = "ProtoShop.VisitOtherShopReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public function VisitOtherShopReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):VisitOtherShopReq
		{
			othuid = undefined;
			this.othuid = msgObj.othuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VisitOtherShopReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}