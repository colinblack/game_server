package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceGroupMember
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceGroupMember";
		public var package_root:*;
		public  var message:*;
		public function RequestAllianceRaceGroupMember(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceGroupMember
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceGroupMember
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}