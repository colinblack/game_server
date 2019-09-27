package com.sanguo.game.server.connectlogic.common.message.ProtoCard
{
	import laya.utils.Byte;
	public class RewardLifeCardReq
	{
		public static const PROTO:String = "ProtoCard.RewardLifeCardReq";
		public var package_root:*;
		public  var message:*;
		public function RewardLifeCardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardLifeCardReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardLifeCardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}