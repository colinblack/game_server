package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class MessageInfo
	{
		public static const PROTO:String = "ProtoMessageBoard.MessageInfo";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var ts:int;
		public var typeId:int;
		public var senderUid:int;
		public var words:Byte;
		public var receiverUid:int;
		public function MessageInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			ts = undefined;
			typeId = undefined;
			senderUid = undefined;
			words = undefined;
			receiverUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.ts = this.ts;
			serializeObj.typeId = this.typeId;
			serializeObj.senderUid = this.senderUid;
			this.words.pos = 0;
			serializeObj.receiverUid = this.receiverUid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):MessageInfo
		{
			id = undefined;
			ts = undefined;
			typeId = undefined;
			senderUid = undefined;
			words = undefined;
			receiverUid = undefined;
			this.id = msgObj.id;
			this.ts = msgObj.ts;
			this.typeId = msgObj.typeId;
			this.senderUid = msgObj.senderUid;
			this.words = new Byte();
			this.words.writeArrayBuffer(msgObj.words);
			this.words.pos = 0;
			this.receiverUid = msgObj.receiverUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MessageInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}