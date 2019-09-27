package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class RequestNPCUser
	{
		public static const PROTO:String = "ProtoNPCUser.RequestNPCUser";
		public var package_root:*;
		public  var message:*;
		public function RequestNPCUser(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestNPCUser
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestNPCUser
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}