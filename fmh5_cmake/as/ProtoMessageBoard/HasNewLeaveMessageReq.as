package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class HasNewLeaveMessageReq
	{
		public static const PROTO:String = "ProtoMessageBoard.HasNewLeaveMessageReq";
		public var package_root:*;
		public  var message:*;
		public function HasNewLeaveMessageReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):HasNewLeaveMessageReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HasNewLeaveMessageReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}