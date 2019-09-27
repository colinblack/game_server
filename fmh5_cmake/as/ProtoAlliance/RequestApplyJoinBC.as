package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestApplyJoinBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestApplyJoinBC";
		public var package_root:*;
		public  var message:*;
		public var allianceId:int;
		public var reason:Byte;
		public var member:AllianceMemberCPP;
		public function RequestApplyJoinBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = undefined;
			reason = undefined;
			member = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = this.allianceId;
			this.reason.pos = 0;
			serializeObj.member = this.member.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestApplyJoinBC
		{
			allianceId = undefined;
			reason = undefined;
			member = undefined;
			this.allianceId = msgObj.allianceId;
			this.reason = new Byte();
			this.reason.writeArrayBuffer(msgObj.reason);
			this.reason.pos = 0;
			this.member = new AllianceMemberCPP(package_root).unserialize(msgObj.member);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestApplyJoinBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}