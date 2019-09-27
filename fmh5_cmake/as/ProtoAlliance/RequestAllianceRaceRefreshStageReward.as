package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceRefreshStageReward
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceRefreshStageReward";
		public var package_root:*;
		public  var message:*;
		public var id:Vector.<int>;
		public function RequestAllianceRaceRefreshStageReward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = [];
			for(var i:int = 0;i < this.id.length;i++)
			{
				serializeObj.id.push(this.id[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceRefreshStageReward
		{
			id = new Vector.<int>();
			for(var i:int = 0;i < msgObj.id.length;i++)
			{
				this.id.push(msgObj.id[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceRefreshStageReward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}