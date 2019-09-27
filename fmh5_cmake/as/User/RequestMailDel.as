package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RequestMailDel
	{
		public static const PROTO:String = "User.RequestMailDel";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public function RequestMailDel(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestMailDel
		{
			ts = undefined;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestMailDel
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}