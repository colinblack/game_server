package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class RewardLifeCardResp
	{
		public static const PROTO:String = "ProtoCard.RewardLifeCardResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var lifeCard:LifeCardCPP;
		public function RewardLifeCardResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			lifeCard = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.lifeCard = this.lifeCard.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardLifeCardResp
		{
			commons = undefined;
			lifeCard = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.lifeCard = new LifeCardCPP(package_root).unserialize(msgObj.lifeCard);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardLifeCardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}