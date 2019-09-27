package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ApplyJoinReq
	{
		public static const PROTO:String = "ProtoAlliance.ApplyJoinReq";
		public var package_root:*;
		public  var message:*;
		public var allianceId:int;
		public var reason:Byte;
		public function ApplyJoinReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = undefined;
			reason = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = this.allianceId;
			this.reason.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ApplyJoinReq
		{
			allianceId = undefined;
			reason = undefined;
			this.allianceId = msgObj.allianceId;
			this.reason = new Byte();
			this.reason.writeArrayBuffer(msgObj.reason);
			this.reason.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ApplyJoinReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}