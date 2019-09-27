package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestInviteJoinUserBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestInviteJoinUserBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var invitedUid:int;
		public var allianceFlag:int;
		public var name:Byte;
		public var allianceName:Byte;
		public function RequestInviteJoinUserBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			invitedUid = undefined;
			allianceFlag = undefined;
			name = undefined;
			allianceName = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.invitedUid = this.invitedUid;
			serializeObj.allianceFlag = this.allianceFlag;
			this.name.pos = 0;
			this.allianceName.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestInviteJoinUserBC
		{
			aid = undefined;
			uid = undefined;
			invitedUid = undefined;
			allianceFlag = undefined;
			name = undefined;
			allianceName = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.invitedUid = msgObj.invitedUid;
			this.allianceFlag = msgObj.allianceFlag;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.allianceName = new Byte();
			this.allianceName.writeArrayBuffer(msgObj.allianceName);
			this.allianceName.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestInviteJoinUserBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}