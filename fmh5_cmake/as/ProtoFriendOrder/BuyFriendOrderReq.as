package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class BuyFriendOrderReq
	{
		public static const PROTO:String = "ProtoFriendOrder.BuyFriendOrderReq";
		public var package_root:*;
		public  var message:*;
		public var index:int;
		public var Status:int;
		public var sourceId:int;
		public var senderUid:int;
		public var productId:int;
		public var count:int;
		public var coin:int;
		public function BuyFriendOrderReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			index = undefined;
			Status = undefined;
			sourceId = undefined;
			senderUid = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.index = this.index;
			serializeObj.Status = this.Status;
			serializeObj.sourceId = this.sourceId;
			serializeObj.senderUid = this.senderUid;
			serializeObj.productId = this.productId;
			serializeObj.count = this.count;
			serializeObj.coin = this.coin;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyFriendOrderReq
		{
			index = undefined;
			Status = undefined;
			sourceId = undefined;
			senderUid = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
			this.index = msgObj.index;
			this.Status = msgObj.Status;
			this.sourceId = msgObj.sourceId;
			this.senderUid = msgObj.senderUid;
			this.productId = msgObj.productId;
			this.count = msgObj.count;
			this.coin = msgObj.coin;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyFriendOrderReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}