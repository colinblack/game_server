package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RequestOtherUser
	{
		public static const PROTO:String = "User.RequestOtherUser";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public function RequestOtherUser(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestOtherUser
		{
			othuid = undefined;
			this.othuid = msgObj.othuid;
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