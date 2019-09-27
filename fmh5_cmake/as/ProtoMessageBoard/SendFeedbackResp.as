package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class SendFeedbackResp
	{
		public static const PROTO:String = "ProtoMessageBoard.SendFeedbackResp";
		public var package_root:*;
		public  var message:*;
		public var yourFeedback:FeedbackInfo;
		public function SendFeedbackResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			yourFeedback = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.yourFeedback = this.yourFeedback.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):SendFeedbackResp
		{
			yourFeedback = undefined;
			this.yourFeedback = new FeedbackInfo(package_root).unserialize(msgObj.yourFeedback);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SendFeedbackResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}