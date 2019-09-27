package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class GetMasterVisiableMsgReq
	{
		public static const PROTO:String = "ProtoMessageBoard.GetMasterVisiableMsgReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var masteruid:int;
		public function GetMasterVisiableMsgReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			masteruid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.masteruid = this.masteruid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetMasterVisiableMsgReq
		{
			myuid = undefined;
			masteruid = undefined;
			this.myuid = msgObj.myuid;
			this.masteruid = msgObj.masteruid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetMasterVisiableMsgReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}