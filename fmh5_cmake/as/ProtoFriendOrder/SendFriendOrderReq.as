package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class SendFriendOrderReq
	{
		public static const PROTO:String = "ProtoFriendOrder.SendFriendOrderReq";
		public var package_root:*;
		public  var message:*;
		public var basket:int;
		public var productId:int;
		public var count:int;
		public var coin:int;
		public var arrayuid:Vector.<int>;
		public function SendFriendOrderReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			basket = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
			arrayuid = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.basket = this.basket;
			serializeObj.productId = this.productId;
			serializeObj.count = this.count;
			serializeObj.coin = this.coin;
			serializeObj.arrayuid = [];
			for(var i:int = 0;i < this.arrayuid.length;i++)
			{
				serializeObj.arrayuid.push(this.arrayuid[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SendFriendOrderReq
		{
			basket = undefined;
			productId = undefined;
			count = undefined;
			coin = undefined;
			arrayuid = new Vector.<int>();
			this.basket = msgObj.basket;
			this.productId = msgObj.productId;
			this.count = msgObj.count;
			this.coin = msgObj.coin;
			for(var i:int = 0;i < msgObj.arrayuid.length;i++)
			{
				this.arrayuid.push(msgObj.arrayuid[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SendFriendOrderReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}