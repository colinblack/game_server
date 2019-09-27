package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class SetFlag
	{
		public static const PROTO:String = "User.SetFlag";
		public var package_root:*;
		public  var message:*;
		public var flagId:int;
		public var isCostDimaond:int;
		public function SetFlag(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			flagId = undefined;
			isCostDimaond = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.flagId = this.flagId;
			if(this.isCostDimaond!= undefined)
			{
				serializeObj.isCostDimaond = this.isCostDimaond;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetFlag
		{
			flagId = undefined;
			isCostDimaond = undefined;
			this.flagId = msgObj.flagId;
			if(msgObj.hasOwnProperty("isCostDimaond"))
			{
				this.isCostDimaond = msgObj.isCostDimaond;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetFlag
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}