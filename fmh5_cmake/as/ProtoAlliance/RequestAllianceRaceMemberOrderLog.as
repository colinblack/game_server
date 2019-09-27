package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceMemberOrderLog
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceMemberOrderLog";
		public var package_root:*;
		public  var message:*;
		public function RequestAllianceRaceMemberOrderLog(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceMemberOrderLog
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceMemberOrderLog
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}