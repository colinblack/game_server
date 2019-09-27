package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class PushBuyMonthCardMsg
	{
		public static const PROTO:String = "ProtoCard.PushBuyMonthCardMsg";
		public var package_root:*;
		public  var message:*;
		public var monthCard:MonthCardCPP;
		public function PushBuyMonthCardMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			monthCard = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.monthCard = this.monthCard.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushBuyMonthCardMsg
		{
			monthCard = undefined;
			this.monthCard = new MonthCardCPP(package_root).unserialize(msgObj.monthCard);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushBuyMonthCardMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}