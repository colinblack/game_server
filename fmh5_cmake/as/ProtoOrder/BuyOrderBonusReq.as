package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class BuyOrderBonusReq
	{
		public static const PROTO:String = "ProtoOrder.BuyOrderBonusReq";
		public var package_root:*;
		public  var message:*;
		public function BuyOrderBonusReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyOrderBonusReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyOrderBonusReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}