package com.sanguo.game.server.connectlogic.common.message.ProtoReward
{
	import laya.utils.Byte;
	public class GetFollowPublicRewardReq
	{
		public static const PROTO:String = "ProtoReward.GetFollowPublicRewardReq";
		public var package_root:*;
		public  var message:*;
		public function GetFollowPublicRewardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFollowPublicRewardReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFollowPublicRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}