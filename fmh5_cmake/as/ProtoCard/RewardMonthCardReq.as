package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class RewardMonthCardReq
	{
		public static const PROTO:String = "ProtoCard.RewardMonthCardReq";
		public var package_root:*;
		public  var message:*;
		public function RewardMonthCardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardMonthCardReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardMonthCardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}