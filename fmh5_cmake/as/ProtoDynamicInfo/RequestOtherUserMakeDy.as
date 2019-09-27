package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class RequestOtherUserMakeDy
	{
		public static const PROTO:String = "ProtoDynamicInfo.RequestOtherUserMakeDy";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var othuid:int;
		public var typeid:int;
		public var productId:int;
		public var coin:int;
		public var words:Byte;
		public function RequestOtherUserMakeDy(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			othuid = undefined;
			typeid = undefined;
			productId = undefined;
			coin = undefined;
			words = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.othuid = this.othuid;
			serializeObj.typeid = this.typeid;
			if(this.productId!= undefined)
			{
				serializeObj.productId = this.productId;
			}
			if(this.coin!= undefined)
			{
				serializeObj.coin = this.coin;
			}
			if(this.words!= undefined)
			{
				serializeObj.words = this.words.getUint8Array(0, this.words.length);
				this.words.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestOtherUserMakeDy
		{
			myuid = undefined;
			othuid = undefined;
			typeid = undefined;
			productId = undefined;
			coin = undefined;
			words = undefined;
			this.myuid = msgObj.myuid;
			this.othuid = msgObj.othuid;
			this.typeid = msgObj.typeid;
			if(msgObj.hasOwnProperty("productId"))
			{
				this.productId = msgObj.productId;
			}
			if(msgObj.hasOwnProperty("coin"))
			{
				this.coin = msgObj.coin;
			}
			if(msgObj.hasOwnProperty("words"))
			{
				this.words = new Byte();
				this.words.writeArrayBuffer(msgObj.words);
				this.words.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestOtherUserMakeDy
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}