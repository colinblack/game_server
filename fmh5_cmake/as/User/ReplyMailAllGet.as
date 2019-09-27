package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ReplyMailAllGet
	{
		public static const PROTO:String = "User.ReplyMailAllGet";
		public var package_root:*;
		public  var message:*;
		public var reward:RewardInfo;
		public function ReplyMailAllGet(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			reward = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.reward!= undefined)
			{
				serializeObj.reward = this.reward.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyMailAllGet
		{
			reward = undefined;
			if(msgObj.hasOwnProperty("reward"))
			{
				this.reward = new RewardInfo(package_root).unserialize(msgObj.reward);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyMailAllGet
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}