package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AcceptInviteReq
	{
		public static const PROTO:String = "ProtoAlliance.AcceptInviteReq";
		public var package_root:*;
		public  var message:*;
		public var allianceId:int;
		public var operate:int;
		public function AcceptInviteReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = undefined;
			operate = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = this.allianceId;
			serializeObj.operate = this.operate;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AcceptInviteReq
		{
			allianceId = undefined;
			operate = undefined;
			this.allianceId = msgObj.allianceId;
			this.operate = msgObj.operate;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AcceptInviteReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}