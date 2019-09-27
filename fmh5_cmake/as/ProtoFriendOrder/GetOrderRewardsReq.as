package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class GetOrderRewardsReq
	{
		public static const PROTO:String = "ProtoFriendOrder.GetOrderRewardsReq";
		public var package_root:*;
		public  var message:*;
		public var basket:int;
		public var Status:int;
		public var productId:int;
		public var count:int;
		public var coin:int;
		public function GetOrderRewardsReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			basket = undefined;
			Status = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.basket = this.basket;
			serializeObj.Status = this.Status;
			serializeObj.productId = this.productId;
			serializeObj.count = this.count;
			serializeObj.coin = this.coin;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetOrderRewardsReq
		{
			basket = undefined;
			Status = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
			this.basket = msgObj.basket;
			this.Status = msgObj.Status;
			this.productId = msgObj.productId;
			this.count = msgObj.count;
			this.coin = msgObj.coin;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetOrderRewardsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}