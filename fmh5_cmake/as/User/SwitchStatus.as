package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class SwitchStatus
	{
		public static const PROTO:String = "User.SwitchStatus";
		public var package_root:*;
		public  var message:*;
		public var switchStatus:int;
		public function SwitchStatus(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			switchStatus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.switchStatus = this.switchStatus;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SwitchStatus
		{
			switchStatus = undefined;
			this.switchStatus = msgObj.switchStatus;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SwitchStatus
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}