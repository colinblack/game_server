package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class CostDiamondReq
	{
		public static const PROTO:String = "ProtoFriendOrder.CostDiamondReq";
		public var package_root:*;
		public  var message:*;
		public var basket:int;
		public var status:int;
		public var diamonds:int;
		public function CostDiamondReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			basket = undefined;
			status = undefined;
			diamonds = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.basket = this.basket;
			serializeObj.status = this.status;
			serializeObj.diamonds = this.diamonds;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CostDiamondReq
		{
			basket = undefined;
			status = undefined;
			diamonds = undefined;
			this.basket = msgObj.basket;
			this.status = msgObj.status;
			this.diamonds = msgObj.diamonds;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CostDiamondReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}