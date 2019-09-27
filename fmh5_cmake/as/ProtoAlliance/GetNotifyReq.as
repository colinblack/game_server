package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class GetNotifyReq
	{
		public static const PROTO:String = "ProtoAlliance.GetNotifyReq";
		public var package_root:*;
		public  var message:*;
		public function GetNotifyReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNotifyReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNotifyReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}