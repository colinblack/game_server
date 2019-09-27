package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class SpeedUpResp
	{
		public static const PROTO:String = "User.SpeedUpResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function SpeedUpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SpeedUpResp
		{
			commons = undefined;
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
		public function decode(buffer:*):SpeedUpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}