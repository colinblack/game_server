package com.sanguo.game.server.connectlogic.common.message.ProtoReward
{
	import laya.utils.Byte;
	public class FetchProductWatchAdsRewardReq
	{
		public static const PROTO:String = "ProtoReward.FetchProductWatchAdsRewardReq";
		public var package_root:*;
		public  var message:*;
		public function FetchProductWatchAdsRewardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):FetchProductWatchAdsRewardReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FetchProductWatchAdsRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}