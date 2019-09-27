package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceInfo
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceInfo";
		public var package_root:*;
		public  var message:*;
		public function RequestAllianceRaceInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceInfo
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}