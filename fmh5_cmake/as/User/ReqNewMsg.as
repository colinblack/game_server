package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ReqNewMsg
	{
		public static const PROTO:String = "User.ReqNewMsg";
		public var package_root:*;
		public  var message:*;
		public function ReqNewMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReqNewMsg
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReqNewMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}