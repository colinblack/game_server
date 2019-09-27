package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class InvitedPushReq
	{
		public static const PROTO:String = "ProtoAlliance.InvitedPushReq";
		public var package_root:*;
		public  var message:*;
		public var invite:AllianceInvitedCPP;
		public function InvitedPushReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			invite = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.invite = this.invite.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):InvitedPushReq
		{
			invite = undefined;
			this.invite = new AllianceInvitedCPP(package_root).unserialize(msgObj.invite);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):InvitedPushReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}