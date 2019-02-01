package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class WinStreakRewardResp
	{
		public static const PROTO:String = "ProtoBattle.WinStreakRewardResp";
		public var package_root:*;
		public  var message:*;
		public var rewards:CommonItemsCPP;
		public function WinStreakRewardResp(root:*)
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
		public function unserialize(msgObj:*):WinStreakRewardResp
		{
			rewards = undefined;
			this.rewards = new CommonItemsCPP(package_root).unserialize(msgObj.rewards);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):WinStreakRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}