package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class CreateAllianceResp
	{
		public static const PROTO:String = "ProtoAlliance.CreateAllianceResp";
		public var package_root:*;
		public  var message:*;
		public var alliance:AllianceCPP;
		public var member:AllianceMemberCPP;
		public var commons:CommonItemsCPP;
		public function CreateAllianceResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			alliance = undefined;
			member = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.alliance = this.alliance.serialize();
			serializeObj.member = this.member.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):CreateAllianceResp
		{
			alliance = undefined;
			member = undefined;
			commons = undefined;
			this.alliance = new AllianceCPP(package_root).unserialize(msgObj.alliance);
			this.member = new AllianceMemberCPP(package_root).unserialize(msgObj.member);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CreateAllianceResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}