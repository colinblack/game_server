package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class CostDiamondResp
	{
		public static const PROTO:String = "ProtoFriendOrder.CostDiamondResp";
		public var package_root:*;
		public  var message:*;
		public var basket:int;
		public var newstatus:int;
		public var commons:CommonItemsCPP;
		public function CostDiamondResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			basket = undefined;
			newstatus = undefined;
			commons = undefined;
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
			return serializeObj;
		}
		public function unserialize(msgObj:*):CostDiamondResp
		{
			basket = undefined;
			newstatus = undefined;
			commons = undefined;
			this.basket = msgObj.basket;
			this.newstatus = msgObj.newstatus;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CostDiamondResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}