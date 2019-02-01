package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UpgradeShareRewardResp
	{
		public static const PROTO:String = "ProtoBattle.UpgradeShareRewardResp";
		public var package_root:*;
		public  var message:*;
		public var rewards:CommonItemsCPP;
		public function UpgradeShareRewardResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			rewards = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.rewards = this.rewards.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):UpgradeShareRewardResp
		{
			rewards = undefined;
			this.rewards = new CommonItemsCPP(package_root).unserialize(msgObj.rewards);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UpgradeShareRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}