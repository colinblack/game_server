package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class InviteActivityUrlReq
	{
		public static const PROTO:String = "User.InviteActivityUrlReq";
		public var package_root:*;
		public  var message:*;
		public var uuid:int;
		public function InviteActivityUrlReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uuid = this.uuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):InviteActivityUrlReq
		{
			uuid = undefined;
			this.uuid = msgObj.uuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):InviteActivityUrlReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}