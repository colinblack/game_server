package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class SendLeaveMsgOverServerReq
	{
		public static const PROTO:String = "ProtoMessageBoard.SendLeaveMsgOverServerReq";
		public var package_root:*;
		public  var message:*;
		public var model:int;
		public var sender:int;
		public var receiver:int;
		public var typeid:int;
		public var words:Byte;
		public function SendLeaveMsgOverServerReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			model = undefined;
			sender = undefined;
			receiver = undefined;
			typeid = undefined;
			words = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.model = this.model;
			serializeObj.sender = this.sender;
			serializeObj.receiver = this.receiver;
			serializeObj.typeid = this.typeid;
			this.words.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SendLeaveMsgOverServerReq
		{
			model = undefined;
			sender = undefined;
			receiver = undefined;
			typeid = undefined;
			words = undefined;
			this.model = msgObj.model;
			this.sender = msgObj.sender;
			this.receiver = msgObj.receiver;
			this.typeid = msgObj.typeid;
			this.words = new Byte();
			this.words.writeArrayBuffer(msgObj.words);
			this.words.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SendLeaveMsgOverServerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}