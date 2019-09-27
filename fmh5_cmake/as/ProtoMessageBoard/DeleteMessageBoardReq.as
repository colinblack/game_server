package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class DeleteMessageBoardReq
	{
		public static const PROTO:String = "ProtoMessageBoard.DeleteMessageBoardReq";
		public var package_root:*;
		public  var message:*;
		public var masteruid:int;
		public var id:int;
		public var typeId:int;
		public var senderUid:int;
		public function DeleteMessageBoardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			masteruid = undefined;
			id = undefined;
			typeId = undefined;
			senderUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.masteruid = this.masteruid;
			serializeObj.id = this.id;
			serializeObj.typeId = this.typeId;
			serializeObj.senderUid = this.senderUid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):DeleteMessageBoardReq
		{
			masteruid = undefined;
			id = undefined;
			typeId = undefined;
			senderUid = undefined;
			this.masteruid = msgObj.masteruid;
			this.id = msgObj.id;
			this.typeId = msgObj.typeId;
			this.senderUid = msgObj.senderUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DeleteMessageBoardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}