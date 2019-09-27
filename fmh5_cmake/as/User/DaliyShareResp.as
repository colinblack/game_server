package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class DaliyShareResp
	{
		public static const PROTO:String = "User.DaliyShareResp";
		public var package_root:*;
		public  var message:*;
		public var days:int;
		public var rewardts:int;
		public function DaliyShareResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			days = undefined;
			rewardts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.days = this.days;
			serializeObj.rewardts = this.rewardts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):DaliyShareResp
		{
			days = undefined;
			rewardts = undefined;
			this.days = msgObj.days;
			this.rewardts = msgObj.rewardts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DaliyShareResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}