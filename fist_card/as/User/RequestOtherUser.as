package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class RequestOtherUser
	{
		public static const PROTO:String = "User.RequestOtherUser";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public function RequestOtherUser(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestOtherUser
		{
			uid = undefined;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestOtherUser
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}