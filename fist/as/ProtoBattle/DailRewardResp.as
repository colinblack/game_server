package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class DailRewardResp
	{
		public static const PROTO:String = "ProtoBattle.DailRewardResp";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var rewards:CommonItemsCPP;
		public function DailRewardResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			ts = undefined;
			rewards = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.rewards = this.rewards.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):DailRewardResp
		{
			ts = undefined;
			rewards = undefined;
			this.ts = msgObj.ts;
			this.rewards = new CommonItemsCPP(package_root).unserialize(msgObj.rewards);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DailRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}