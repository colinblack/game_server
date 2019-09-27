package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class SendFeedbackReq
	{
		public static const PROTO:String = "ProtoMessageBoard.SendFeedbackReq";
		public var package_root:*;
		public  var message:*;
		public var words:Byte;
		public function SendFeedbackReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			words = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			this.words.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SendFeedbackReq
		{
			words = undefined;
			this.words = new Byte();
			this.words.writeArrayBuffer(msgObj.words);
			this.words.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SendFeedbackReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}