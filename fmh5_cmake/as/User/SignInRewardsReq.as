package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class SignInRewardsReq
	{
		public static const PROTO:String = "User.SignInRewardsReq";
		public var package_root:*;
		public  var message:*;
		public var day:int;
		public function SignInRewardsReq(root:*)
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
		public function unserialize(msgObj:*):SignInRewardsReq
		{
			day = undefined;
			this.day = msgObj.day;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SignInRewardsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}