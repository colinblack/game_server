package com.sanguo.game.server.connectlogic.common.message.ProtoMission
{
	import laya.utils.Byte;
	public class PushMission
	{
		public static const PROTO:String = "ProtoMission.PushMission";
		public var package_root:*;
		public  var message:*;
		public var mission:MissionCPP;
		public function PushMission(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			mission = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.mission = this.mission.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushMission
		{
			mission = undefined;
			this.mission = new MissionCPP(package_root).unserialize(msgObj.mission);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushMission
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}