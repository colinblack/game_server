package com.sanguo.game.server.connectlogic.common.message.ProtoReward
{
	import laya.utils.Byte;
	public class GetFirstRechargeRewardReq
	{
		public static const PROTO:String = "ProtoReward.GetFirstRechargeRewardReq";
		public var package_root:*;
		public  var message:*;
		public function GetFirstRechargeRewardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFirstRechargeRewardReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFirstRechargeRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}