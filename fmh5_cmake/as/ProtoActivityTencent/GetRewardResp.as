package com.sanguo.game.server.connectlogic.common.message.ProtoActivityTencent
{
	import laya.utils.Byte;
	public class GetRewardResp
	{
		public static const PROTO:String = "ProtoActivityTencent.GetRewardResp";
		public var package_root:*;
		public  var message:*;
		public var status:RewardStatusResp;
		public var reward:RewardInfo;
		public function GetRewardResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			status = undefined;
			reward = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.status!= undefined)
			{
				serializeObj.status = this.status.serialize();
			}
			if(this.reward!= undefined)
			{
				serializeObj.reward = this.reward.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetRewardResp
		{
			status = undefined;
			reward = undefined;
			if(msgObj.hasOwnProperty("status"))
			{
				this.status = new RewardStatusResp(package_root).unserialize(msgObj.status);
			}
			if(msgObj.hasOwnProperty("reward"))
			{
				this.reward = new RewardInfo(package_root).unserialize(msgObj.reward);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}