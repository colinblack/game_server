package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class FeedbackInfo
	{
		public static const PROTO:String = "ProtoMessageBoard.FeedbackInfo";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var ts:int;
		public var words:Byte;
		public function FeedbackInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			ts = undefined;
			words = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.ts = this.ts;
			this.words.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):FeedbackInfo
		{
			id = undefined;
			ts = undefined;
			words = undefined;
			this.id = msgObj.id;
			this.ts = msgObj.ts;
			this.words = new Byte();
			this.words.writeArrayBuffer(msgObj.words);
			this.words.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FeedbackInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}