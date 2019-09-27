package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class SpeedUpReq
	{
		public static const PROTO:String = "User.SpeedUpReq";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public var ud:int;
		public var method:int;
		public function SpeedUpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
			ud = undefined;
			method = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			if(this.ud!= undefined)
			{
				serializeObj.ud = this.ud;
			}
			if(this.method!= undefined)
			{
				serializeObj.method = this.method;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SpeedUpReq
		{
			type = undefined;
			ud = undefined;
			method = undefined;
			this.type = msgObj.type;
			if(msgObj.hasOwnProperty("ud"))
			{
				this.ud = msgObj.ud;
			}
			if(msgObj.hasOwnProperty("method"))
			{
				this.method = msgObj.method;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SpeedUpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}