package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class ReplySysMail
	{
		public static const PROTO:String = "Admin.ReplySysMail";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public function ReplySysMail(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ret = this.ret;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplySysMail
		{
			ret = undefined;
			this.ret = msgObj.ret;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplySysMail
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}