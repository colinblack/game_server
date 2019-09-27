package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class GetFlagResp
	{
		public static const PROTO:String = "User.GetFlagResp";
		public var package_root:*;
		public  var message:*;
		public var flag:int;
		public var commons:CommonItemsCPP;
		public function GetFlagResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			flag = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.flag = this.flag;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFlagResp
		{
			flag = undefined;
			commons = undefined;
			this.flag = msgObj.flag;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFlagResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}