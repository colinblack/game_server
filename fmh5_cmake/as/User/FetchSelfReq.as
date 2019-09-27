package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class FetchSelfReq
	{
		public static const PROTO:String = "User.FetchSelfReq";
		public var package_root:*;
		public  var message:*;
		public function FetchSelfReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):FetchSelfReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FetchSelfReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}