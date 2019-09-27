package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestApproveJoinAllianceBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestApproveJoinAllianceBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var operate:int;
		public var member:AllianceMemberCPP;
		public function RequestApproveJoinAllianceBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			operate = undefined;
			member = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.operate = this.operate;
			serializeObj.member = this.member.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestApproveJoinAllianceBC
		{
			aid = undefined;
			uid = undefined;
			operate = undefined;
			member = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.operate = msgObj.operate;
			this.member = new AllianceMemberCPP(package_root).unserialize(msgObj.member);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestApproveJoinAllianceBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}