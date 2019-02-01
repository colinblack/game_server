package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class SpeedUpReq
	{
		public static const PROTO:String = "User.SpeedUpReq";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public var ud:int;
		public function SpeedUpReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			type = undefined;
			ud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			if(this.ud!= undefined)
			{
				serializeObj.ud = this.ud;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SpeedUpReq
		{
			type = undefined;
			ud = undefined;
			this.type = msgObj.type;
			if(msgObj.hasOwnProperty("ud"))
			{
				this.ud = msgObj.ud;
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