package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ShareRewardsReq
	{
		public static const PROTO:String = "User.ShareRewardsReq";
		public var package_root:*;
		public  var message:*;
		public function ShareRewardsReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShareRewardsReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShareRewardsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}