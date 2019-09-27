package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class InviteJoinResp
	{
		public static const PROTO:String = "ProtoAlliance.InviteJoinResp";
		public var package_root:*;
		public  var message:*;
		public var invitedUid:int;
		public function InviteJoinResp(root:*)
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
		public function unserialize(msgObj:*):InviteJoinResp
		{
			invitedUid = undefined;
			this.invitedUid = msgObj.invitedUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):InviteJoinResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}