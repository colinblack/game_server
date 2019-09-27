package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class ShareFriendCPP
	{
		public static const PROTO:String = "ProtoActivity.ShareFriendCPP";
		public var package_root:*;
		public  var message:*;
		public var friendUid:int;
		public var inviteTs:int;
		public function ShareFriendCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			friendUid = undefined;
			inviteTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.friendUid = this.friendUid;
			serializeObj.inviteTs = this.inviteTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShareFriendCPP
		{
			friendUid = undefined;
			inviteTs = undefined;
			this.friendUid = msgObj.friendUid;
			this.inviteTs = msgObj.inviteTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShareFriendCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}