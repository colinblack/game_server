package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAlliance
	{
		public static const PROTO:String = "ProtoAlliance.RequestAlliance";
		public var package_root:*;
		public  var message:*;
		public function RequestAlliance(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAlliance
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAlliance
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}