package com.sanguo.game.server.connectlogic.common.message.ProtoPush
{
	import laya.utils.Byte;
	public class RewardLevelUpResp
	{
		public static const PROTO:String = "ProtoPush.RewardLevelUpResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function RewardLevelUpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardLevelUpResp
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardLevelUpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}