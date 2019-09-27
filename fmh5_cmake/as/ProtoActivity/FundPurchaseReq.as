package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class FundPurchaseReq
	{
		public static const PROTO:String = "ProtoActivity.FundPurchaseReq";
		public var package_root:*;
		public  var message:*;
		public function FundPurchaseReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):FundPurchaseReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FundPurchaseReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}