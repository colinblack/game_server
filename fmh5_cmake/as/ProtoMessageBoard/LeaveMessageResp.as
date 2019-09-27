package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class LeaveMessageResp
	{
		public static const PROTO:String = "ProtoMessageBoard.LeaveMessageResp";
		public var package_root:*;
		public  var message:*;
		public var newMsg:MessageInfo;
		public function LeaveMessageResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			newMsg = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.newMsg = this.newMsg.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):LeaveMessageResp
		{
			newMsg = undefined;
			this.newMsg = new MessageInfo(package_root).unserialize(msgObj.newMsg);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):LeaveMessageResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}