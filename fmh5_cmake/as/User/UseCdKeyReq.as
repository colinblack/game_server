package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class UseCdKeyReq
	{
		public static const PROTO:String = "User.UseCdKeyReq";
		public var package_root:*;
		public  var message:*;
		public var number:String;
		public function UseCdKeyReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			number = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.number = this.number;
			return serializeObj;
		}
		public function unserialize(msgObj:*):UseCdKeyReq
		{
			number = undefined;
			this.number = msgObj.number;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UseCdKeyReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}