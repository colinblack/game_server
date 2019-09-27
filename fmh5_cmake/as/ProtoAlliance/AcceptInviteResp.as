package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AcceptInviteResp
	{
		public static const PROTO:String = "ProtoAlliance.AcceptInviteResp";
		public var package_root:*;
		public  var message:*;
		public var allianceId:int;
		public var operate:int;
		public var member:AllianceMemberCPP;
		public var commons:CommonItemsCPP;
		public var alliance:AllianceCPP;
		public function AcceptInviteResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = undefined;
			operate = undefined;
			member = undefined;
			commons = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = this.allianceId;
			serializeObj.operate = this.operate;
			if(this.member!= undefined)
			{
				serializeObj.member = this.member.serialize();
			}
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):AcceptInviteResp
		{
			allianceId = undefined;
			operate = undefined;
			member = undefined;
			commons = undefined;
			alliance = undefined;
			this.allianceId = msgObj.allianceId;
			this.operate = msgObj.operate;
			if(msgObj.hasOwnProperty("member"))
			{
				this.member = new AllianceMemberCPP(package_root).unserialize(msgObj.member);
			}
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new AllianceCPP(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AcceptInviteResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}