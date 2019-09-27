package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class MonthCardCPP
	{
		public static const PROTO:String = "ProtoCard.MonthCardCPP";
		public var package_root:*;
		public  var message:*;
		public var isHaveMonthCard:int;
		public var isReward:int;
		public var monthCardEndTs:int;
		public function MonthCardCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			isHaveMonthCard = undefined;
			isReward = undefined;
			monthCardEndTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.isHaveMonthCard = this.isHaveMonthCard;
			if(this.isReward!= undefined)
			{
				serializeObj.isReward = this.isReward;
			}
			if(this.monthCardEndTs!= undefined)
			{
				serializeObj.monthCardEndTs = this.monthCardEndTs;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MonthCardCPP
		{
			isHaveMonthCard = undefined;
			isReward = undefined;
			monthCardEndTs = undefined;
			this.isHaveMonthCard = msgObj.isHaveMonthCard;
			if(msgObj.hasOwnProperty("isReward"))
			{
				this.isReward = msgObj.isReward;
			}
			if(msgObj.hasOwnProperty("monthCardEndTs"))
			{
				this.monthCardEndTs = msgObj.monthCardEndTs;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MonthCardCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}