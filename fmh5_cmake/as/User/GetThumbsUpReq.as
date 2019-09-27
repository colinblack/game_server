package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class GetThumbsUpReq
	{
		public static const PROTO:String = "User.GetThumbsUpReq";
		public var package_root:*;
		public  var message:*;
		public function GetThumbsUpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetThumbsUpReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetThumbsUpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}