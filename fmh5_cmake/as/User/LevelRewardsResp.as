package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class LevelRewardsResp
	{
		public static const PROTO:String = "User.LevelRewardsResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function LevelRewardsResp(root:*)
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
		public function unserialize(msgObj:*):LevelRewardsResp
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):LevelRewardsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}