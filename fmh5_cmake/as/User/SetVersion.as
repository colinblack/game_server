package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class SetVersion
	{
		public static const PROTO:String = "User.SetVersion";
		public var package_root:*;
		public  var message:*;
		public var version:int;
		public function SetVersion(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			version = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.version = this.version;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetVersion
		{
			version = undefined;
			this.version = msgObj.version;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetVersion
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}