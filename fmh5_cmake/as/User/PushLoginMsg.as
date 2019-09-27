package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class PushLoginMsg
	{
		public static const PROTO:String = "User.PushLoginMsg";
		public var package_root:*;
		public  var message:*;
		public var loginTs:int;
		public var uid:int;
		public function PushLoginMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			loginTs = undefined;
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.loginTs = this.loginTs;
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushLoginMsg
		{
			loginTs = undefined;
			uid = undefined;
			this.loginTs = msgObj.loginTs;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushLoginMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}