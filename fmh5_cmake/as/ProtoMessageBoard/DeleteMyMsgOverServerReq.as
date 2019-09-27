package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class DeleteMyMsgOverServerReq
	{
		public static const PROTO:String = "ProtoMessageBoard.DeleteMyMsgOverServerReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var masteruid:int;
		public var id:int;
		public function DeleteMyMsgOverServerReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			masteruid = undefined;
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.masteruid = this.masteruid;
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):DeleteMyMsgOverServerReq
		{
			myuid = undefined;
			masteruid = undefined;
			id = undefined;
			this.myuid = msgObj.myuid;
			this.masteruid = msgObj.masteruid;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DeleteMyMsgOverServerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}