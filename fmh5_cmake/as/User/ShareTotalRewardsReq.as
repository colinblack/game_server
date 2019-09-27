package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ShareTotalRewardsReq
	{
		public static const PROTO:String = "User.ShareTotalRewardsReq";
		public var package_root:*;
		public  var message:*;
		public var day:int;
		public function ShareTotalRewardsReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			day = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.day = this.day;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShareTotalRewardsReq
		{
			day = undefined;
			this.day = msgObj.day;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShareTotalRewardsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}