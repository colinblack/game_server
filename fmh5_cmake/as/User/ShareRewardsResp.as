package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ShareRewardsResp
	{
		public static const PROTO:String = "User.ShareRewardsResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var rewardts:int;
		public function ShareRewardsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			rewardts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.rewardts = this.rewardts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShareRewardsResp
		{
			commons = undefined;
			rewardts = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.rewardts = msgObj.rewardts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShareRewardsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}