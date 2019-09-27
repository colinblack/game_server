package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class GetMemberReq
	{
		public static const PROTO:String = "ProtoAlliance.GetMemberReq";
		public var package_root:*;
		public  var message:*;
		public var allianceId:int;
		public function GetMemberReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = this.allianceId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetMemberReq
		{
			allianceId = undefined;
			this.allianceId = msgObj.allianceId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetMemberReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}