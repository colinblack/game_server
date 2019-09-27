package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceInvitedCPP
	{
		public static const PROTO:String = "ProtoAlliance.AllianceInvitedCPP";
		public var package_root:*;
		public  var message:*;
		public var inviteUid:int;
		public var allianceId:int;
		public var allianceName:Byte;
		public var flag:int;
		public var inviteName:Byte;
		public var invitets:int;
		public function AllianceInvitedCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			inviteUid = undefined;
			allianceId = undefined;
			allianceName = undefined;
			flag = undefined;
			inviteName = undefined;
			invitets = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.inviteUid = this.inviteUid;
			serializeObj.allianceId = this.allianceId;
			this.allianceName.pos = 0;
			serializeObj.flag = this.flag;
			this.inviteName.pos = 0;
			serializeObj.invitets = this.invitets;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceInvitedCPP
		{
			inviteUid = undefined;
			allianceId = undefined;
			allianceName = undefined;
			flag = undefined;
			inviteName = undefined;
			invitets = undefined;
			this.inviteUid = msgObj.inviteUid;
			this.allianceId = msgObj.allianceId;
			this.allianceName = new Byte();
			this.allianceName.writeArrayBuffer(msgObj.allianceName);
			this.allianceName.pos = 0;
			this.flag = msgObj.flag;
			this.inviteName = new Byte();
			this.inviteName.writeArrayBuffer(msgObj.inviteName);
			this.inviteName.pos = 0;
			this.invitets = msgObj.invitets;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceInvitedCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}