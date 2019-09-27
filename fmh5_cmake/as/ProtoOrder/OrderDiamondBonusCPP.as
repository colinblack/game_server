package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class OrderDiamondBonusCPP
	{
		public static const PROTO:String = "ProtoOrder.OrderDiamondBonusCPP";
		public var package_root:*;
		public  var message:*;
		public var remainDiamondBonusCnt:int;
		public var diamondBonusEndTs:int;
		public function OrderDiamondBonusCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			remainDiamondBonusCnt = undefined;
			diamondBonusEndTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.remainDiamondBonusCnt = this.remainDiamondBonusCnt;
			serializeObj.diamondBonusEndTs = this.diamondBonusEndTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OrderDiamondBonusCPP
		{
			remainDiamondBonusCnt = undefined;
			diamondBonusEndTs = undefined;
			this.remainDiamondBonusCnt = msgObj.remainDiamondBonusCnt;
			this.diamondBonusEndTs = msgObj.diamondBonusEndTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OrderDiamondBonusCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}