package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class GetOrderRewardsResp
	{
		public static const PROTO:String = "ProtoFriendOrder.GetOrderRewardsResp";
		public var package_root:*;
		public  var message:*;
		public var basket:int;
		public var newstatus:int;
		public var commons:CommonItemsCPP;
		public var deadtime:int;
		public function GetOrderRewardsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			basket = undefined;
			newstatus = undefined;
			commons = undefined;
			deadtime = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.basket = this.basket;
			serializeObj.newstatus = this.newstatus;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			if(this.deadtime!= undefined)
			{
				serializeObj.deadtime = this.deadtime;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetOrderRewardsResp
		{
			basket = undefined;
			newstatus = undefined;
			commons = undefined;
			deadtime = undefined;
			this.basket = msgObj.basket;
			this.newstatus = msgObj.newstatus;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			if(msgObj.hasOwnProperty("deadtime"))
			{
				this.deadtime = msgObj.deadtime;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetOrderRewardsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}