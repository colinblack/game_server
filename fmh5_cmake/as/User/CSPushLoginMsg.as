package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class CSPushLoginMsg
	{
		public static const PROTO:String = "User.CSPushLoginMsg";
		public var package_root:*;
		public  var message:*;
		public var inviteUid:int;
		public var loginTs:int;
		public var uid:int;
		public function CSPushLoginMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			inviteUid = undefined;
			loginTs = undefined;
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.inviteUid = this.inviteUid;
			serializeObj.loginTs = this.loginTs;
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSPushLoginMsg
		{
			inviteUid = undefined;
			loginTs = undefined;
			uid = undefined;
			this.inviteUid = msgObj.inviteUid;
			this.loginTs = msgObj.loginTs;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSPushLoginMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}