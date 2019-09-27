package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class PushBuyLifeCardMsg
	{
		public static const PROTO:String = "ProtoCard.PushBuyLifeCardMsg";
		public var package_root:*;
		public  var message:*;
		public var lifeCard:LifeCardCPP;
		public function PushBuyLifeCardMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			lifeCard = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.lifeCard = this.lifeCard.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushBuyLifeCardMsg
		{
			lifeCard = undefined;
			this.lifeCard = new LifeCardCPP(package_root).unserialize(msgObj.lifeCard);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushBuyLifeCardMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}