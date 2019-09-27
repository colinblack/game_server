package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class GetFeedbackReq
	{
		public static const PROTO:String = "ProtoMessageBoard.GetFeedbackReq";
		public var package_root:*;
		public  var message:*;
		public function GetFeedbackReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFeedbackReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFeedbackReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}