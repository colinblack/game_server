package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAcceptInviteBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestAcceptInviteBC";
		public var package_root:*;
		public  var message:*;
		public var allianceId:int;
		public var inviteUid:int;
		public var operate:int;
		public var member:AllianceMemberCPP;
		public function RequestAcceptInviteBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = undefined;
			inviteUid = undefined;
			operate = undefined;
			member = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = this.allianceId;
			serializeObj.inviteUid = this.inviteUid;
			serializeObj.operate = this.operate;
			if(this.member!= undefined)
			{
				serializeObj.member = this.member.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAcceptInviteBC
		{
			allianceId = undefined;
			inviteUid = undefined;
			operate = undefined;
			member = undefined;
			this.allianceId = msgObj.allianceId;
			this.inviteUid = msgObj.inviteUid;
			this.operate = msgObj.operate;
			if(msgObj.hasOwnProperty("member"))
			{
				this.member = new AllianceMemberCPP(package_root).unserialize(msgObj.member);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAcceptInviteBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}