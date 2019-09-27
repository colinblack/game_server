package com.sanguo.game.server.connectlogic.common.message.ProtoActivityTencent
{
	import laya.utils.Byte;
	public class RewardStatusReq
	{
		public static const PROTO:String = "ProtoActivityTencent.RewardStatusReq";
		public var package_root:*;
		public  var message:*;
		public function RewardStatusReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardStatusReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardStatusReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}