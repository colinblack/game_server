package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class SignInRewardsResp
	{
		public static const PROTO:String = "User.SignInRewardsResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var marks:int;
		public function SignInRewardsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			marks = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			serializeObj.marks = this.marks;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SignInRewardsResp
		{
			commons = undefined;
			marks = undefined;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			this.marks = msgObj.marks;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SignInRewardsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}