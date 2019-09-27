package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class RewardViewAdReq
	{
		public static const PROTO:String = "ProtoAccessAd.RewardViewAdReq";
		public var package_root:*;
		public  var message:*;
		public function RewardViewAdReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardViewAdReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardViewAdReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}