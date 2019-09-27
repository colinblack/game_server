package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class RewardNewShareResp
	{
		public static const PROTO:String = "ProtoActivity.RewardNewShareResp";
		public var package_root:*;
		public  var message:*;
		public var rewardFlag:Vector.<int>;
		public var common:CommonItemsCPP;
		public function RewardNewShareResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			rewardFlag = new Vector.<int>();
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.rewardFlag = [];
			for(var i:int = 0;i < this.rewardFlag.length;i++)
			{
				serializeObj.rewardFlag.push(this.rewardFlag[i]);
			}
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardNewShareResp
		{
			rewardFlag = new Vector.<int>();
			common = undefined;
			for(var i:int = 0;i < msgObj.rewardFlag.length;i++)
			{
				this.rewardFlag.push(msgObj.rewardFlag[i]);
			}
			this.common = new CommonItemsCPP(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardNewShareResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}