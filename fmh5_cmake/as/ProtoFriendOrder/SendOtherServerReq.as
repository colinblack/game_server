package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class SendOtherServerReq
	{
		public static const PROTO:String = "ProtoFriendOrder.SendOtherServerReq";
		public var package_root:*;
		public  var message:*;
		public var status:int;
		public var senderUid:int;
		public var deadtime:int;
		public var sourceId:int;
		public var productId:int;
		public var count:int;
		public var coin:int;
		public var receiverUid:int;
		public function SendOtherServerReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			status = undefined;
			senderUid = undefined;
			deadtime = undefined;
			sourceId = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
			receiverUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.status = this.status;
			serializeObj.senderUid = this.senderUid;
			serializeObj.deadtime = this.deadtime;
			serializeObj.sourceId = this.sourceId;
			serializeObj.productId = this.productId;
			serializeObj.count = this.count;
			serializeObj.coin = this.coin;
			serializeObj.receiverUid = this.receiverUid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SendOtherServerReq
		{
			status = undefined;
			senderUid = undefined;
			deadtime = undefined;
			sourceId = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
			receiverUid = undefined;
			this.status = msgObj.status;
			this.senderUid = msgObj.senderUid;
			this.deadtime = msgObj.deadtime;
			this.sourceId = msgObj.sourceId;
			this.productId = msgObj.productId;
			this.count = msgObj.count;
			this.coin = msgObj.coin;
			this.receiverUid = msgObj.receiverUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SendOtherServerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}