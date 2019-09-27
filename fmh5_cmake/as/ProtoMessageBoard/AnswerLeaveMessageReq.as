package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class AnswerLeaveMessageReq
	{
		public static const PROTO:String = "ProtoMessageBoard.AnswerLeaveMessageReq";
		public var package_root:*;
		public  var message:*;
		public var senderUid:int;
		public var typeId:int;
		public var words:Byte;
		public function AnswerLeaveMessageReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			senderUid = undefined;
			typeId = undefined;
			words = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.senderUid = this.senderUid;
			serializeObj.typeId = this.typeId;
			this.words.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AnswerLeaveMessageReq
		{
			senderUid = undefined;
			typeId = undefined;
			words = undefined;
			this.senderUid = msgObj.senderUid;
			this.typeId = msgObj.typeId;
			this.words = new Byte();
			this.words.writeArrayBuffer(msgObj.words);
			this.words.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AnswerLeaveMessageReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}