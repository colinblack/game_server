package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class GetCardResp
	{
		public static const PROTO:String = "ProtoCard.GetCardResp";
		public var package_root:*;
		public  var message:*;
		public var monthCard:MonthCardCPP;
		public var lifeCard:LifeCardCPP;
		public function GetCardResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			monthCard = undefined;
			lifeCard = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.monthCard = this.monthCard.serialize();
			serializeObj.lifeCard = this.lifeCard.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetCardResp
		{
			monthCard = undefined;
			lifeCard = undefined;
			this.monthCard = new MonthCardCPP(package_root).unserialize(msgObj.monthCard);
			this.lifeCard = new LifeCardCPP(package_root).unserialize(msgObj.lifeCard);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetCardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}