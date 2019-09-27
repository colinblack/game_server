package com.sanguo.game.server.connectlogic.common.message.ProtoMission
{
	import laya.utils.Byte;
	public class RewardMissionResp
	{
		public static const PROTO:String = "ProtoMission.RewardMissionResp";
		public var package_root:*;
		public  var message:*;
		public var missions:Vector.<MissionCPP>;
		public var commons:CommonItemsCPP;
		public function RewardMissionResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			missions = new Vector.<MissionCPP>();
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.missions = [];
			for(var i:int = 0;i < this.missions.length;i++)
			{
				serializeObj.missions.push(this.missions[i].serialize());
			}
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardMissionResp
		{
			missions = new Vector.<MissionCPP>();
			commons = undefined;
			for(var i:int = 0;i < msgObj.missions.length;i++)
			{
				this.missions.push(new MissionCPP(package_root).unserialize(msgObj.missions[i]));
			}
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardMissionResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}