package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class FriendOrderInfo
	{
		public static const PROTO:String = "ProtoFriendOrder.FriendOrderInfo";
		public var package_root:*;
		public  var message:*;
		public var status:int;
		public var senderUid:int;
		public var deadtime:int;
		public var sourceId:int;
		public var HelperUid:int;
		public var productId:int;
		public var count:int;
		public var coin:int;
		public var index:int;
		public function FriendOrderInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			status = undefined;
			senderUid = undefined;
			deadtime = undefined;
			sourceId = undefined;
			HelperUid = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
			index = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.status = this.status;
			serializeObj.senderUid = this.senderUid;
			serializeObj.deadtime = this.deadtime;
			serializeObj.sourceId = this.sourceId;
			if(this.HelperUid!= undefined)
			{
				serializeObj.HelperUid = this.HelperUid;
			}
			serializeObj.productId = this.productId;
			serializeObj.count = this.count;
			serializeObj.coin = this.coin;
			serializeObj.index = this.index;
			return serializeObj;
		}
		public function unserialize(msgObj:*):FriendOrderInfo
		{
			status = undefined;
			senderUid = undefined;
			deadtime = undefined;
			sourceId = undefined;
			HelperUid = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
			index = undefined;
			this.status = msgObj.status;
			this.senderUid = msgObj.senderUid;
			this.deadtime = msgObj.deadtime;
			this.sourceId = msgObj.sourceId;
			if(msgObj.hasOwnProperty("HelperUid"))
			{
				this.HelperUid = msgObj.HelperUid;
			}
			this.productId = msgObj.productId;
			this.count = msgObj.count;
			this.coin = msgObj.coin;
			this.index = msgObj.index;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FriendOrderInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}