package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRacePersonOrderLog
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRacePersonOrderLog";
		public var package_root:*;
		public  var message:*;
		public function RequestAllianceRacePersonOrderLog(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRacePersonOrderLog
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRacePersonOrderLog
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}