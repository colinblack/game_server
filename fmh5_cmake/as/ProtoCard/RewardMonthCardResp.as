package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class RewardMonthCardResp
	{
		public static const PROTO:String = "ProtoCard.RewardMonthCardResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var monthCard:MonthCardCPP;
		public function RewardMonthCardResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			monthCard = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.monthCard = this.monthCard.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardMonthCardResp
		{
			commons = undefined;
			monthCard = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.monthCard = new MonthCardCPP(package_root).unserialize(msgObj.monthCard);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardMonthCardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}