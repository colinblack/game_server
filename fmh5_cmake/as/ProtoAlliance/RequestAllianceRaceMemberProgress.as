package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceMemberProgress
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceMemberProgress";
		public var package_root:*;
		public  var message:*;
		public function RequestAllianceRaceMemberProgress(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceMemberProgress
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceMemberProgress
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}