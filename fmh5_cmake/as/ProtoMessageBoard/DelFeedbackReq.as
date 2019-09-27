package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class DelFeedbackReq
	{
		public static const PROTO:String = "ProtoMessageBoard.DelFeedbackReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function DelFeedbackReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):DelFeedbackReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DelFeedbackReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}