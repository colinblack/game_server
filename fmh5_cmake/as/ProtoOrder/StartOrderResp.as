package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class StartOrderResp
	{
		public static const PROTO:String = "ProtoOrder.StartOrderResp";
		public var package_root:*;
		public  var message:*;
		public var result:Boolean;
		public var commons:CommonItemsCPP;
		public var order:OrderCPP;
		public var truck:TruckCPP;
		public var adBonus:OrderADBonusCPP;
		public var diamondBounus:OrderDiamondBonusCPP;
		public var vipBonus:OrderVIPBonusCPP;
		public function StartOrderResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			result = undefined;
			commons = undefined;
			order = undefined;
			truck = undefined;
			adBonus = undefined;
			diamondBounus = undefined;
			vipBonus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.result = this.result;
			serializeObj.commons = this.commons.serialize();
			serializeObj.order = this.order.serialize();
			serializeObj.truck = this.truck.serialize();
			if(this.adBonus!= undefined)
			{
				serializeObj.adBonus = this.adBonus.serialize();
			}
			if(this.diamondBounus!= undefined)
			{
				serializeObj.diamondBounus = this.diamondBounus.serialize();
			}
			if(this.vipBonus!= undefined)
			{
				serializeObj.vipBonus = this.vipBonus.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):StartOrderResp
		{
			result = undefined;
			commons = undefined;
			order = undefined;
			truck = undefined;
			adBonus = undefined;
			diamondBounus = undefined;
			vipBonus = undefined;
			this.result = msgObj.result;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.order = new OrderCPP(package_root).unserialize(msgObj.order);
			this.truck = new TruckCPP(package_root).unserialize(msgObj.truck);
			if(msgObj.hasOwnProperty("adBonus"))
			{
				this.adBonus = new OrderADBonusCPP(package_root).unserialize(msgObj.adBonus);
			}
			if(msgObj.hasOwnProperty("diamondBounus"))
			{
				this.diamondBounus = new OrderDiamondBonusCPP(package_root).unserialize(msgObj.diamondBounus);
			}
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
		public function decode(buffer:*):StartOrderResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}