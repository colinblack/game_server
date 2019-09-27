package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class BuyOrderBonusResp
	{
		public static const PROTO:String = "ProtoOrder.BuyOrderBonusResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var diamondBounus:OrderDiamondBonusCPP;
		public function BuyOrderBonusResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			diamondBounus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.diamondBounus = this.diamondBounus.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyOrderBonusResp
		{
			commons = undefined;
			diamondBounus = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.diamondBounus = new OrderDiamondBonusCPP(package_root).unserialize(msgObj.diamondBounus);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyOrderBonusResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}