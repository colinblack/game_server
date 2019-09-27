package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class OrderVIPBonusCPP
	{
		public static const PROTO:String = "ProtoOrder.OrderVIPBonusCPP";
		public var package_root:*;
		public  var message:*;
		public var remainVipBonusCnt:int;
		public function OrderVIPBonusCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			remainVipBonusCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.remainVipBonusCnt = this.remainVipBonusCnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OrderVIPBonusCPP
		{
			remainVipBonusCnt = undefined;
			this.remainVipBonusCnt = msgObj.remainVipBonusCnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OrderVIPBonusCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}