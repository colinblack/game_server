package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ShareTotalRewardsResp
	{
		public static const PROTO:String = "User.ShareTotalRewardsResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var marks:int;
		public function ShareTotalRewardsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			marks = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.marks = this.marks;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShareTotalRewardsResp
		{
			commons = undefined;
			marks = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.marks = msgObj.marks;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShareTotalRewardsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}