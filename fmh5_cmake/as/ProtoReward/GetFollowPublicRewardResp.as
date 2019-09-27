package com.sanguo.game.server.connectlogic.common.message.ProtoReward
{
	import laya.utils.Byte;
	public class GetFollowPublicRewardResp
	{
		public static const PROTO:String = "ProtoReward.GetFollowPublicRewardResp";
		public var package_root:*;
		public  var message:*;
		public var common:CommonItemsCPP;
		public function GetFollowPublicRewardResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFollowPublicRewardResp
		{
			common = undefined;
			this.common = new CommonItemsCPP(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFollowPublicRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}