package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceTakeGradeReward
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceTakeGradeReward";
		public var package_root:*;
		public  var message:*;
		public function RequestAllianceRaceTakeGradeReward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceTakeGradeReward
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceTakeGradeReward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}