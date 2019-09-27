package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ReplyMailGet
	{
		public static const PROTO:String = "User.ReplyMailGet";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var stat:int;
		public var reward:RewardInfo;
		public function ReplyMailGet(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
			stat = undefined;
			reward = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.stat = this.stat;
			if(this.reward!= undefined)
			{
				serializeObj.reward = this.reward.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyMailGet
		{
			ts = undefined;
			stat = undefined;
			reward = undefined;
			this.ts = msgObj.ts;
			this.stat = msgObj.stat;
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
		public function decode(buffer:*):ReplyMailGet
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}