package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class DynamicInfo
	{
		public static const PROTO:String = "ProtoDynamicInfo.DynamicInfo";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var ts:int;
		public var typeId:int;
		public var opUid:int;
		public var productId:int;
		public var coin:int;
		public var words:Byte;
		public function DynamicInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			ts = undefined;
			typeId = undefined;
			opUid = undefined;
			productId = undefined;
			coin = undefined;
			words = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.ts = this.ts;
			serializeObj.typeId = this.typeId;
			if(this.opUid!= undefined)
			{
				serializeObj.opUid = this.opUid;
			}
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
		public function unserialize(msgObj:*):DynamicInfo
		{
			id = undefined;
			ts = undefined;
			typeId = undefined;
			opUid = undefined;
			productId = undefined;
			coin = undefined;
			words = undefined;
			this.id = msgObj.id;
			this.ts = msgObj.ts;
			this.typeId = msgObj.typeId;
			if(msgObj.hasOwnProperty("opUid"))
			{
				this.opUid = msgObj.opUid;
			}
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
		public function decode(buffer:*):DynamicInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}