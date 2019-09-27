package com.sanguo.game.server.connectlogic.common.message.ProtoReward
{
	import laya.utils.Byte;
	public class FetchProductWatchAdsReward
	{
		public static const PROTO:String = "ProtoReward.FetchProductWatchAdsReward";
		public var package_root:*;
		public  var message:*;
		public var propsId:int;
		public var count:int;
		public function FetchProductWatchAdsReward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			propsId = undefined;
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propsId = this.propsId;
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):FetchProductWatchAdsReward
		{
			propsId = undefined;
			count = undefined;
			this.propsId = msgObj.propsId;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FetchProductWatchAdsReward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}