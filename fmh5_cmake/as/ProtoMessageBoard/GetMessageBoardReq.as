package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class GetMessageBoardReq
	{
		public static const PROTO:String = "ProtoMessageBoard.GetMessageBoardReq";
		public var package_root:*;
		public  var message:*;
		public var masteruid:int;
		public function GetMessageBoardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			masteruid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.masteruid = this.masteruid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetMessageBoardReq
		{
			masteruid = undefined;
			this.masteruid = msgObj.masteruid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetMessageBoardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}