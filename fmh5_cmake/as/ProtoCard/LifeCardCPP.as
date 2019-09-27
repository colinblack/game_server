package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class LifeCardCPP
	{
		public static const PROTO:String = "ProtoCard.LifeCardCPP";
		public var package_root:*;
		public  var message:*;
		public var isHaveLifeCard:int;
		public var isReward:int;
		public function LifeCardCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			isHaveLifeCard = undefined;
			isReward = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.isHaveLifeCard = this.isHaveLifeCard;
			if(this.isReward!= undefined)
			{
				serializeObj.isReward = this.isReward;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):LifeCardCPP
		{
			isHaveLifeCard = undefined;
			isReward = undefined;
			this.isHaveLifeCard = msgObj.isHaveLifeCard;
			if(msgObj.hasOwnProperty("isReward"))
			{
				this.isReward = msgObj.isReward;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):LifeCardCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}