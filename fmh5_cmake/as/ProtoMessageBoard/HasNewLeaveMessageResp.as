package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class HasNewLeaveMessageResp
	{
		public static const PROTO:String = "ProtoMessageBoard.HasNewLeaveMessageResp";
		public var package_root:*;
		public  var message:*;
		public var HasNewMsg:Boolean;
		public function HasNewLeaveMessageResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			HasNewMsg = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.HasNewMsg = this.HasNewMsg;
			return serializeObj;
		}
		public function unserialize(msgObj:*):HasNewLeaveMessageResp
		{
			HasNewMsg = undefined;
			this.HasNewMsg = msgObj.HasNewMsg;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HasNewLeaveMessageResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}