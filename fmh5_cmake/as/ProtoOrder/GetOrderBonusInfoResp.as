package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class GetOrderBonusInfoResp
	{
		public static const PROTO:String = "ProtoOrder.GetOrderBonusInfoResp";
		public var package_root:*;
		public  var message:*;
		public var adBonus:OrderADBonusCPP;
		public var diamondBounus:OrderDiamondBonusCPP;
		public var vipBonus:OrderVIPBonusCPP;
		public function GetOrderBonusInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			adBonus = undefined;
			diamondBounus = undefined;
			vipBonus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.adBonus = this.adBonus.serialize();
			serializeObj.diamondBounus = this.diamondBounus.serialize();
			if(this.vipBonus!= undefined)
			{
				serializeObj.vipBonus = this.vipBonus.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetOrderBonusInfoResp
		{
			adBonus = undefined;
			diamondBounus = undefined;
			vipBonus = undefined;
			this.adBonus = new OrderADBonusCPP(package_root).unserialize(msgObj.adBonus);
			this.diamondBounus = new OrderDiamondBonusCPP(package_root).unserialize(msgObj.diamondBounus);
			if(msgObj.hasOwnProperty("vipBonus"))
			{
				this.vipBonus = new OrderVIPBonusCPP(package_root).unserialize(msgObj.vipBonus);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetOrderBonusInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}