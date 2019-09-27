package com.sanguo.game.server.connectlogic.common.message.ProtoPush
{
	import laya.utils.Byte;
	public class RewardLevelUpReq
	{
		public static const PROTO:String = "ProtoPush.RewardLevelUpReq";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public function RewardLevelUpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardLevelUpReq
		{
			type = undefined;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardLevelUpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}