package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class CSInviteActivityUrlReq
	{
		public static const PROTO:String = "User.CSInviteActivityUrlReq";
		public var package_root:*;
		public  var message:*;
		public var uuid:int;
		public var uid:int;
		public function CSInviteActivityUrlReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uuid = undefined;
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uuid = this.uuid;
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSInviteActivityUrlReq
		{
			uuid = undefined;
			uid = undefined;
			this.uuid = msgObj.uuid;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSInviteActivityUrlReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}