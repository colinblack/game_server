package com.sanguo.game.server.connectlogic.common.message.Common
{
	import laya.utils.Byte;
	public class Pay
	{
		public static const PROTO:String = "Common.Pay";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var cash:int;
		public var ts:int;
		public var itemid:int;
		public var currency:int;
		public var tradeNo:Byte;
		public var channelTradeNo:Byte;
		public function Pay(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			cash = undefined;
			ts = undefined;
			itemid = undefined;
			currency = undefined;
			tradeNo = undefined;
			channelTradeNo = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.cash = this.cash;
			serializeObj.ts = this.ts;
			if(this.itemid!= undefined)
			{
				serializeObj.itemid = this.itemid;
			}
			if(this.currency!= undefined)
			{
				serializeObj.currency = this.currency;
			}
			if(this.tradeNo!= undefined)
			{
				serializeObj.tradeNo = this.tradeNo.getUint8Array(0, this.tradeNo.length);
				this.tradeNo.pos = 0;
			}
			if(this.channelTradeNo!= undefined)
			{
				serializeObj.channelTradeNo = this.channelTradeNo.getUint8Array(0, this.channelTradeNo.length);
				this.channelTradeNo.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):Pay
		{
			uid = undefined;
			cash = undefined;
			ts = undefined;
			itemid = undefined;
			currency = undefined;
			tradeNo = undefined;
			channelTradeNo = undefined;
			this.uid = msgObj.uid;
			this.cash = msgObj.cash;
			this.ts = msgObj.ts;
			if(msgObj.hasOwnProperty("itemid"))
			{
				this.itemid = msgObj.itemid;
			}
			if(msgObj.hasOwnProperty("currency"))
			{
				this.currency = msgObj.currency;
			}
			if(msgObj.hasOwnProperty("tradeNo"))
			{
				this.tradeNo = new Byte();
				this.tradeNo.writeArrayBuffer(msgObj.tradeNo);
				this.tradeNo.pos = 0;
			}
			if(msgObj.hasOwnProperty("channelTradeNo"))
			{
				this.channelTradeNo = new Byte();
				this.channelTradeNo.writeArrayBuffer(msgObj.channelTradeNo);
				this.channelTradeNo.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):Pay
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}