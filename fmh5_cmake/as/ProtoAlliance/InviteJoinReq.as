package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class InviteJoinReq
	{
		public static const PROTO:String = "ProtoAlliance.InviteJoinReq";
		public var package_root:*;
		public  var message:*;
		public var invitedUid:int;
		public function InviteJoinReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			invitedUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.invitedUid = this.invitedUid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):InviteJoinReq
		{
			invitedUid = undefined;
			this.invitedUid = msgObj.invitedUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):InviteJoinReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}